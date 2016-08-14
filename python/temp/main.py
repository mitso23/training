import xml.etree.ElementTree as ET
import requests
import gzip
import os
from subprocess import Popen, PIPE
import zipfile
import StringIO

def useSshPassCopy():
	sshCommand = "sshpass -p linaro scp -r UpdateJM linaro@192.168.0.8:/tmp"
	os.system(sshCommand)

def useScpCopy():
	proc = Popen(['scp', "UpdateJM.tar.gz", "linaro@192.168.0.8:/tmp"], stdin = PIPE)
	proc.stdin.write(b'linaro\n')
	#proc.stdin.flush()	

def main() :
	tree = ET.parse('config.xml')
	root = tree.getroot()
	
	quickBuildElement = root.find("quickbuild_number")	
	testBenchIpElement = root.find("test_board_ip")
	
	#Extract the useful config elements from the xml
	quickbuildNumber = quickBuildElement.text
	testBenchIp = 	testBenchIpElement.text
	print("Quickbuild number is "  + quickbuildNumber  + " test bench IP is " + testBenchIp )
	
	# Download the file
	#fname = 'testrail-5.2.0.3452-ion53.zip'
	#url = 'https://secure.gurock.com/downloads/testrail/testrail-5.2.0.3452-ion53.zip'
	#r = requests.get(url)
	#open(fname , 'wb').write(r.content)

	#gunzip
	with gzip.open('UpdateJM.zip.gz', 'rb') as f:
		file_content = f.read()
		open('UpdateJM.zip', 'wb').write(file_content)
	
	#unzip the file
	zip = zipfile.ZipFile('UpdateJM.zip')
	zip.extractall();
	
	useSshPassCopy()


if __name__ == '__main__':
    main()
