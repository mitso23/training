#include <algorithm>

#define LOG_INFO(X) //std::cout << X << std::endl;
#define LOG_DEBUG(X) //std::cout << X << std::endl;
#define LOG_TRACE(X) //std::cout << X << std::endl;

#define MAX_STAGES 100
#define MAX_TOOLS  50
#define MAX_LOTS 100000

namespace pipeline
{


/*
 *  Stage 0:
 *
 *  t = 0;  WaitingList (A=0, B=0) : Tool(10, C=5), Tool(20, D=10)
 *  t = 0;  ProcessingList(C=5, D=10) : Next()
 *
 *  1) Find item with smallest processing time in the processing list and decrease the time by the tick amount
 *      1.1) if  the time is zero move it the next list (to be processed by the next stage of the pipeline)
 *          1.11) The next list should contain also the current time of the item
 *          1.12) This means that the item will not be processed until that time is reached on the next pipeline
 *      1.2) if the time is zero then mark the tool as available
 *      1.3) Go to the next item in the processing list and decrease the time by the tick amount and go to step 1.2 if the time is zero
 *      1.4) go through the waiting list and move the first item with time 0 to the tool with the smallest processing time
 *          1.41)If we can't find any empty tool we stop
 *          1.42) If we can't process the first item in the waiting list we stop
 *      1.5) add the item to the processing list in sorted order
 *
 *
 *  t = 5; WaitingList(B=0) : Tool(10, A=10) , Tool(20, D=5)
 *  t = 5; ProcessingList(D=5, A=10) : Next(C=5)
 *
 *  t = 10; WaitingList() : Tool(10, A=5) , Tool(20, B=20)
 *  t = 10; ProcessingList(A=5) : Next(C=5, D=10)
 *
 *  t = 15; WaitingList() : Tool(10, A=5) , Tool(20, B=20)
 *  t = 15; ProcessingList(A=5, B=20) : Next(C=5, D=10)
 *
 *  t = 20; WaitingList() : Tool(10) , Tool(20, B=15)
 *  t = 20; ProcessingList(B=15) : Next(C=5, D=10, A=20)
 *
 *  t = 35; WaitingList() : Tool(10) , Tool(20, )
 *  t = 35; ProcessingList() : Next(C=5, D=10, A=20, B=35)
 *
 *
 *  Stage 1
 *
 *  1) get the list from the previous pipelines
 *      1.1 (C=5, D=10, A=20, B=35)
 *
 *  t = 0;  WaitingList (E=0) : Tool(10, F=10)
 *  t = 0;  ProcessingList(F=10) : Next()
 *
 *  2) Append the list from previous pipeline to current one (the list will be in sorted order)
 *
 *  t = 0;  WaitingList (E=0, C=5, D=10, A=20, B=35) : Tool(10, F=10)
 *  t = 0;  ProcessingList(F=10) : Next()
 *
 *  t = 10; WaitingList (C=5, D=10, A=20, B=35) : Tool(10, E=10)
 *  t = 10; ProcessingList(E=10) : Next(F=10)
 *
 *  t = 20; WaitingList (D=10, A=20, B=35) : Tool(10, C=10)
 *  t = 20; ProcessingList(C=10) : Next(F=10, E=20)
 *
 *  t = 30; WaitingList (A=20, B=35) : Tool(10, D=10)
 *  t = 30; ProcessingList(D=10) : Next(F=10, E=20, C=30)
 *
 *  t = 40; WaitingList (B=35) : Tool(10, A=10)
 *  t = 40; ProcessingList(A=10) : Next(F=10, E=20, C=30, D=40)
 *
 *  t = 50; WaitingList () : Tool(10, B=10)
 *  t = 50; ProcessingList(B=10) : Next(F=10, E=20, C=30, D=40, A=50)
 *
 *  t = 60; WaitingList () : Tool(10)
 *  t = 60; ProcessingList() : Next(F=10, E=20, C=30, D=40, A=50, B=60)
 *
 *  Stage 2 (IDLE)
 *
 *  1) get the list from the previous pipelines
 *      1.1 (F=10, E=20, C=30, D=40, A=50, B=60)
 *
 *  t = 0;  WaitingList () : Tool(5), Tool(10)
 *  t = 0;  ProcessingList() : Next()
 *
 *  2) merge with the existing waiting list
 *
 *  t = 0;  WaitingList (F=10, E=20, C=30, D=40, A=50, B=60) : Tool(5), Tool(10)
 *  t = 0;  ProcessingList() : Next()
 *
 *  3) since processing list is empty we go through the waiting list
 *
 *  t = 10; WaitingList (E=20, C=30, D=40, A=50, B=60) : Tool(5, F=10), Tool(10)
 *  t = 10; ProcessingList(F=10) : Next()
 *
 *  t = 20; WaitingList (C=30, D=40, A=50, B=60) : Tool(5, E=5), Tool(10)
 *  t = 20; ProcessingList(E=5) : Next(F=10)
 *
 *  t = 25; WaitingList (C=30, D=40, A=50, B=60) : Tool(5,), Tool(10)
 *  t = 25; ProcessingList() : Next(F=10, E=25)
 *
 *  t = 30; WaitingList (D=40, A=50, B=60) : Tool(5, C=5), Tool(10)
 *  t = 30; ProcessingList(C=5) : Next(F=10, E=25)
 *
 *  t = 35; WaitingList (D=40, A=50, B=60) : Tool(5), Tool(10)
 *  t = 35; ProcessingList() : Next(F=10, E=25, C=35)
 *
 *  t = 40; WaitingList (A=50, B=60) : Tool(5, D=5), Tool(10)
 *  t = 40; ProcessingList(D=5) : Next(F=10, E=25, C=35)
 *
 *  t = 45; WaitingList (A=50, B=60) : Tool(5), Tool(10)
 *  t = 45; ProcessingList() : Next(F=10, E=25, C=35, D=45)
 *
 *  t = 50; WaitingList (B=60) : Tool(5, A=5), Tool(10)
 *  t = 50; ProcessingList(A=5) : Next(F=10, E=25, C=35, D=45)
 *
 *  t = 55; WaitingList (B=60) : Tool(5), Tool(10)
 *  t = 55; ProcessingList() : Next(F=10, E=25, C=35, D=45, A=55)
 *
 *  t = 60; WaitingList () : Tool(5), Tool(10)
 *  t = 60; ProcessingList() : Next(F=10, E=25, C=35, D=45, A=55, B=60)
 *
 *
 *  Warehouse
 *
 *  All items after 60 seconds will be in the warehouse
 *
 *  F=10, E=25, C=35, D=45, A=55, B=60
 *
 */

// 130 lines of comments

//30min implementation 120lines
//60min implementation 230lines
//90min implementation 270
//2.5h  implementation 370 lines
//3h debugging link list issues + some time calculation was wrong
//2h design work

//1h to implement memory pool allocator (try not to initialize variables to save some time) 1.5seconds reduced to 0.8seconds

struct Lot
{
    int time = 0;
    int toolId = -1;
};

struct Tool
{
    int processingTime = 0;
    bool active = false;
};

struct Node
{
    Lot data;
    Node* next = nullptr;
    Node* previous = nullptr;
};

struct SimpleAllocator
{

    static void Initialize()
    {
        //lastFreeIndex = 0;
        if (!lots)
        {
            lots = new Node[1024*1024*20];
        }
    }

    static inline Node* Allocate()
    {
        return &lots[lastFreeIndex++];
        //return new Node();
        for(int i=0; i<MAX_LOTS; ++i)
        {
            auto index = (lastFreeIndex + i) % MAX_LOTS;

            if (lots[index].data.toolId == -1)
            {
                LOG_TRACE("allocation at " << index);

                ++lastFreeIndex;
                return &lots[index];
            }
            else
            {
                LOG_TRACE("Missed allocation" << index);
            }
        }

        return nullptr;
    }

    static void Free(Node* lot)
    {
       lot->data.toolId = -1;
    }

    static unsigned int lastFreeIndex;
  //  static Node lots[100000];
    static Node* lots;
};

unsigned int SimpleAllocator::lastFreeIndex = 0;
//Node SimpleAllocator::lots[100000];
Node* SimpleAllocator::lots = nullptr;

struct List
{
    Node* head = nullptr;
    Node* tail = nullptr;
    unsigned int numberItems = 0;

    //Add item to the end of the list
    void AddEnd(const Lot& data)
    {
        if (!head || !tail)
        {
            head = SimpleAllocator::Allocate();
            head->data = data;

            tail = head;

            LOG_INFO("Adding first item with time: " << data.time);
        }
        // T N
        // T next N
        // T previous N
        else
        {
            Node* node = SimpleAllocator::Allocate();
            node->data = data;

            tail->next = node;

            node->previous = tail;

            tail = node;

            LOG_INFO("Adding to the end: " << data.time);
        }

        ++numberItems;
    }

    // 5 10 15 20
    // insert 12
    // 5 10 12 15 20
    void AddSorted(const Lot& data)
    {
        if (!head)
        {
            head = SimpleAllocator::Allocate();
            head->data = data;

            tail = head;

            LOG_INFO("sorted: Adding first item: " << data.time);
            ++numberItems;
            return;
        }

        Node* next = head;
        Node* previous = nullptr;

        while(next && data.time > next->data.time)
        {
            previous = next;
            next= next->next;
        }

        Node* node = SimpleAllocator::Allocate();
        node->data = data;

        node->previous = previous;
        node->next = next;

        if (previous && next)
        {
            LOG_INFO("sorted: adding time " << data.time << " after: " << previous->data.time << " before: " << next->data.time);

            next->previous = node;
            previous->next = node;
        }
        else if (previous)
        {
            LOG_INFO("sorted: adding time " << data.time << " after: " << previous->data.time << " (old tail)");

            previous->next = node;

            tail = node;
        }
        else if (next)
        {
            LOG_INFO("sorted: adding time " << data.time << " before head: " << next->data.time);

            next->previous = node;
            head = node;
        }

        ++numberItems;
    }

    void Print()
    {
        LOG_DEBUG("print");

        Node* current = head;
        while(current)
        {
            LOG_DEBUG("time: " << current->data.time);
            current = current->next;
        }

        LOG_DEBUG("exit print");
    }


    // P C N
    // P->next = C->next
    // N->previous = C->previous
    void RemoveItem(Node* node)
    {
        LOG_DEBUG("Removing item: " << node->data.time);

        Node* previous = node->previous;
        Node* next = node->next;

        if(previous)
        {
            previous->next = next;
        }

        if (next)
        {
            next->previous = previous;
        }

        if (node == tail)
        {
            LOG_DEBUG("removing tail");
            tail = previous;
        }

        if (node == head)
        {
           LOG_DEBUG("removing head");
           head = next;
        }

        --numberItems;
        SimpleAllocator::Free(node);
    }

    void MergeList(List* list)
    {
        LOG_DEBUG("merge");

        if (!list->head)
        {
            LOG_DEBUG("current list empty so merge = list1");
        }
        else if (!tail)
        {
           LOG_DEBUG("List empty so merge = list2");
           tail = list->tail;
           head = list->head;
        }
        else
        {
            LOG_DEBUG("appending to tail");
            tail->next = list->head;
            tail = list->tail;
        }

        numberItems+= list->numberItems;
    }

    void Clear()
    {
        Node* current = head;
        while(current)
        {
            LOG_DEBUG("Clearing item, time: " << current->data.time << " id: " << current->data.toolId);
            Node* next = current->next;
            SimpleAllocator::Free(current);
            current = next;
        }

        head = nullptr;
        tail = nullptr;
        numberItems = 0;

    }
};

struct Stage
{
    ~Stage()
    {
        LOG_DEBUG("Destroying stage: " << id);

        if (id == 0xFF)
        {
            return;
        }

        for(unsigned int i=0; i< numberTools; ++i)
        {
            tools[i].active = false;
            tools[i].processingTime = 0;
        }

        numberTools = 0;
        LOG_DEBUG("Clear waiting list");
        waitingList.Clear();

        LOG_DEBUG("Clear processing list");

        processingList.Clear();
        id = 0;
        stages = nullptr;
        previousTime = 0;
    }

    int GetNumberFreeTools()
    {
        return (numberTools - processingList.numberItems);
    }

    Tool GetFirstFreeTool(int& id)
    {
        for(int i=0; i< numberTools; ++i)
        {
            if (!tools[i].active)
            {
                id = i;
                return tools[i];
            }
        }
    }

    void AddTool(const Tool& tool)
    {
        tools[numberTools++] = tool;
    }

    void SetStagesInfo(Stage* stages_, int id_)
    {
        stages = stages_;
        id = id_;
    }

    void SortTools()
    {
        auto l = [](const Tool& l, const Tool& r)
        {
            return l.processingTime < r.processingTime;
        };
        std::sort(&tools[0], &tools[numberTools - 1], l);
    }

    //This should be called only for stage 0
    void AddLot(int numberLots)
    {
        auto numIter = std::min(numberTools, numberLots);

        for(int i = 0; i< numIter; ++i)
        {
            if (!tools[i].active)
            {
                LOG_INFO("Adding lot to tool with processing time: " << tools[i].processingTime);
                tools[i].active = true;

                Lot lot;
                lot.time = tools[i].processingTime;
                lot.toolId = i;

                processingList.AddSorted(lot);
                --numberLots;
            }
        }

        for(int i=0; i< numberLots; ++i)
        {
            Lot lot;
            LOG_INFO("Adding lot to waiting list");
            waitingList.AddEnd(lot);

        }
    }

    //Core functionality
    List* Process(int simulatedTime, int wip[MAX_STAGES])
    {
        LOG_DEBUG("Current pipeline is " << id << " simulated time: " <<
                  simulatedTime << " previous time: " << previousTime << " waiting list: " << waitingList.numberItems << " processing list: " << processingList.numberItems);

        //waitingList.Print();
        //processingList.Print();

        if (id != 0)
        {
            //Get the list from the previous pipeline
            auto previousWaitingList = stages[id - 1].Process(simulatedTime, wip);
            if (previousWaitingList)
            {
                LOG_INFO("previous waiting list size:  " << previousWaitingList->numberItems);
            }
            else
            {
                LOG_INFO("Previous waiting list is empty");
            }

            if (previousWaitingList)
            {
                waitingList.MergeList(previousWaitingList);
            }

            LOG_INFO("merged waiting list size:  " << waitingList.numberItems);

        }



        if (waitingList.numberItems == 0 && processingList.numberItems == 0)
        {
            LOG_INFO("waiting and processing list are empty");

            wip[id] = 0;
            return nullptr;
        }

        //We start from previousTime and go up to simulated time by tick steps
        auto currentTime = previousTime;
        auto elapsedTime = simulatedTime - previousTime;
        auto currentTick = 0;

        List* waitingListForNextPipeline = new List();

        while(currentTime < simulatedTime)
        {
            //go through the processing list
            {
                Node* current = processingList.head;

                //if we have items in the processing list, the current tick comes from the first element
                if (current)
                {
                    Lot firstItem = current->data;
                    currentTick = std::min(firstItem.time, elapsedTime);
                    currentTime+=currentTick;
                }

                // go through all the elements and decrease the remaining time in the processing list by currentTick
                while(current)
                {
                    Node* next = current->next;
                    Lot& currentItem = current->data;

                    LOG_INFO("Next item from processing time is: " << currentItem.time << " tool id: " << currentItem.toolId);
                    LOG_INFO("tick: " << currentTick << " currentTime: " << currentTime);

                    if (currentItem.time - currentTick <=0)
                    {
                        //mark the tool as available
                        tools[currentItem.toolId].active = false;
                        LOG_DEBUG("Marking tool with id: " << currentItem.toolId << " inactive");

                        //Remove this from the list
                        processingList.RemoveItem(current);

                        //Add this to the next waiting list that will be handled by the next pipeline
                        Lot nextStageProcessing;
                        nextStageProcessing.time = currentTime;
                        LOG_INFO("Adding item to waiting list of next pipeline");
                        waitingListForNextPipeline->AddEnd(nextStageProcessing);

                    }
                    else
                    {
                        //we can just decrease the time
                        currentItem.time-= currentTick;
                        LOG_INFO("Decreasing time of the processing item to: " << currentItem.time);
                    }

                    current = next;
                }
            }

            //Go through the waiting list
            {
                int numberFreeTools = GetNumberFreeTools();
                LOG_INFO("Number of free tools: " << numberFreeTools);

                if (processingList.numberItems == 0)
                {
                    LOG_INFO("Processing list is empty");

                    if (waitingList.head)
                    {
                        auto waitingTime = std::min(waitingList.head->data.time, simulatedTime);
                        //make sure we don't go backwards in time
                        currentTime = std::max(currentTime, waitingTime);

                        LOG_INFO("Current tick is determined by the first item in waiting list: " << currentTime);
                    }
                    else
                    {
                        LOG_INFO("no more items it the waiting list, stopping");
                        currentTime = simulatedTime;
                        break;
                    }
                }

                for(int i=0; i< numberFreeTools; ++i)
                {
                    Node* current = waitingList.head;
                    if (!current)
                    {
                        LOG_INFO("No more items in the waiting list");
                        break;
                    }

                    if (current->data.time <= currentTime)
                    {
                        LOG_INFO("waiting list item time: " << current->data.time << " moving to processing list");

                        int id = 0;
                        Tool tool = GetFirstFreeTool(id);
                        LOG_INFO("First available tool time: " << tool.processingTime << " id: " << id);

                        Lot lot;
                        lot.time = tool.processingTime;
                        lot.toolId = id;

                        processingList.AddSorted(lot);
                        tools[id].active = true;
                        waitingList.RemoveItem(current);
                    }
                    else
                    {
                        LOG_INFO("Current time is smaller than waiting time: " << current->data.time << " not moving to processing list");
                    }
                }
            }


        }

        previousTime = simulatedTime;
        LOG_INFO("finishing stage with number of items in processing list " << processingList.numberItems << " number of done items: " << waitingListForNextPipeline->numberItems);
        wip[id] = processingList.numberItems;
        return waitingListForNextPipeline;

    }

    int numberTools = 0;

    List waitingList;
    List processingList;
    Tool tools[MAX_TOOLS];
    Stage* stages;
    int id = 0xFF;
    int previousTime = 0;
};

Stage gStages[MAX_STAGES];
int gNumStages = 0;
int gNumFinishedTasks = 0;

void init(int numSteps)
{
    for(int i=0; i< gNumStages; ++i)
    {
        LOG_DEBUG("Destroying stage: " << i);
        gStages[i].~Stage();
    }

    gNumStages = numSteps;
    gNumFinishedTasks = 0;
    SimpleAllocator::Initialize();
}

void setupTool(int length, int stages[], int processingTime[])
{
    for(int i=0; i< length; ++i)
    {
        Tool tool;
        tool.processingTime = processingTime[i];

        gStages[stages[i]].AddTool(tool);
        gStages[stages[i]].SetStagesInfo(gStages, stages[i]);
    }

    for(int i=0; i< gNumStages; ++i)
    {
        gStages[i].SortTools();
    }
}

void AddLot(int numberLots)
{
    gStages[0].AddLot(numberLots);
}

int Simulate(int time, int wip[MAX_STAGES])
{

    List* finishedTasks = gStages[gNumStages - 1].Process(time, wip);
    if (finishedTasks)
    {
        LOG_INFO("Number of tasks that finished: " << finishedTasks->numberItems);
        gNumFinishedTasks+= finishedTasks->numberItems;
    }
    else
    {
        LOG_INFO("None of the tasks finished");
    }

    return gNumFinishedTasks;
}

};
