//
// Created by tvkey on 5/9/20.
//

#include <fstream>
#include <iostream>
#include <vector>
#include <iomanip>
#include <map>

std::map<uint16_t, uint64_t> pidToPCR;

#define LOG_INFO(X) 	std::cout << "function: " << __FUNCTION__ << " line: " << __LINE__ << " :: " << X << std::endl;
#define LOG_ERROR(X) 	//std::cout << "function: " << __FUNCTION__ << " line: " << __LINE__ << " :: " << X << std::endl;
#define LOG_DEBUG(X) 	//std::cout << "function: " << __FUNCTION__ << " line: " << __LINE__ << " :: "  << X << std::endl;


template<typename RandomIterator>
bool ParseAdaptaionField(RandomIterator& it, uint16_t pid, int offset)
{
    uint8_t length = *it++;
    LOG_INFO("adaptation field length: " << (unsigned)length);

    uint8_t flags = *it++;

    if (flags & 0x80)
    {
        LOG_ERROR("Discontinuity detected");
        return false;
    }

    if (flags & 0x40)
    {
        LOG_INFO("Stream can be decoded from now on");
    }

    if (flags & 0x10)
    {
        uint64_t pcr;
        pcr = ((uint64_t)(*it) << 25) | (*(it + 1) << 17) | (*(it + 2) << 9) |
               (*(it + 3) << 1) | (*(it + 4) >> 7);

        // Plus the program clock reference extension
        //pcr = ((pcr) * 300) + ((*(it + 4) & 1) << 1) + *(it + 5);
        if (pidToPCR.find(pid) == std::end(pidToPCR))
        {
            pidToPCR[pid] = pcr;
            LOG_INFO("First PCR for pid: " <<  std::hex << pid << std::setw(2) << std::setfill('0') << " PCR: " << pcr << " offset: " << offset);
        }
        else
        {
            auto lastPid = pidToPCR[pid];
            pidToPCR[pid] = pcr;

            LOG_INFO("PCR is present for pid: " <<  std::hex << pid << std::setw(2) << std::setfill('0') << " PCR: " << pcr << " diff: " << std::dec << pcr - lastPid << " time diff: " << (((float)pcr - lastPid) * 1.0f/90000) << " offset: " << offset);
        }
    }

    if (flags & 0x04)
    {
        LOG_INFO("Splice count is present");
    }
}

int main(int argc, char* argv[])
{
    std::ifstream videoFile("/home/tvkey/boa.ts");
    if (!videoFile.good())
    {
        LOG_ERROR(" falied to open file: " << std::endl);
        return -1;
    }

    std::vector<uint8_t> data;
    data.resize(188*1024*1024);
    auto offset = 0;
    while(videoFile.read(reinterpret_cast<char*>(&data.at(offset)), 188))
    {
        auto it = data.begin() + offset;

        if (*it++ != 0x47)
        {
            LOG_ERROR(" invalid sync byte" << std::endl);
            return -1;
        }

        uint16_t pid;
        {
            uint16_t nextVal = (*it << 8) + *(++it);
            if (nextVal & 0x8000)
            {
                LOG_ERROR("transport error indicator " << std::endl);
                return -1;
            }

            if (nextVal & 0x4000)
            {
                LOG_INFO("packet payloads begins after this packet");
            }

            pid = nextVal & 0x1fff;
            LOG_INFO("pid: " << std::hex << pid <<  " number: " << std::dec << (offset/188));

            if (pid == 0)
            {
                LOG_INFO("PAT");
            }
            else if (pid == 1)
            {
                LOG_INFO("CAT");
            }

            ++it;
        }

        uint8_t nextVal = *it++;
        if (nextVal & 0x40)
        {
            LOG_ERROR("reserved");
        }
        else if (nextVal & 0x80)
        {
            LOG_DEBUG(" scrambled with even key");
        }
        else if (nextVal & 0xc0)
        {
            LOG_DEBUG( " scrambled with odd key ");
        }
        else
        {
            LOG_DEBUG("Not scrambled: ");
        }

        if ((nextVal & 0x30) == 0x10)
        {
            LOG_DEBUG("no adaptation field");
        }
        else if ((nextVal & 0x30) == 0x20)
        {
            LOG_INFO("adaptation field no payload ");
            ParseAdaptaionField(it, pid, offset);
        }
        else if ((nextVal & 0x30) == 0x30)
        {
            LOG_INFO("adaptation followed by payload");
            ParseAdaptaionField(it, pid, offset);
        }
        else
        {
            LOG_ERROR("Reserved: " << (nextVal & 0x30));
        }

        LOG_DEBUG("continuity counter: " << (nextVal & 0xf));

        offset+=188;
    }

    std::ofstream outputFile("/home/tvkey/boa_changes.ts");
    outputFile.write((char*)&data.at(0), data.size());

}
