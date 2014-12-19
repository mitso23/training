import sys
import xml.etree.ElementTree as ET

# This is a generic function to get cross point success responses
# The return value is a dictionary with a sequence as a key 
def getCrossPointSuccessResponses(fileName) :
	crossPointSuccessResponses= { }	
	
	try :

		tree = ET.parse(fileName)
		root = tree.getroot()
		for response in root.findall('Response'):
			for crosspointSuccess in response.findall("CrosspointSuccess") :
				crossPointSuccessResponses[crosspointSuccess[0].text]= {'timeStamp' : response.attrib['timeStamp'], 
										        'srcId' : crosspointSuccess[1][0].text, 'dstId' : crosspointSuccess[1][1].text ,  
											'error' : crosspointSuccess[2].text}
	except:
		print("Exception caught: ", sys.exc_info())	
		raise Exception('Failed to parse cross point success response');
	
	return crossPointSuccessResponses

# This is a generic function to get all the cross point requests
# The return value is a dictionary with a sequence as a key 
def getCrossPointRequests(fileName) :
	crossPointRequests= { }	
	
	try :
		tree = ET.parse(fileName)
		root = tree.getroot()
		
		for request in root.findall('Request'):
			for requestSwitch in request.findall("RequestSwitch") :
				crossPointRequests[requestSwitch[0].text]= {'timeStamp' : request.attrib['timeStamp'], 
									    'srcId' : requestSwitch[1][0].text, 'dstId' : requestSwitch[1][1].text }
	except :
		print("Exception caught: ", sys.exc_info())	
		raise Exception('Failed to parse cross point requests');
	
	return crossPointRequests	


#This function executes the simple switch test case scenario
def executeSimpleSwitchesTestCase() :

	try :
		f = open('simpleTestCaseCommand', 'w')
		
		f.write("rd -D 0 \n")
		f.write("rd -D 1 \n")
		f.write("rs -S 0 -D 0 \n")
		f.write("del -t 1000 \n")
		f.write("rs -S 1 -D 1 \n")
		f.write("del -t 1000 \n")

	except :
		print("Exception caught: ", sys.exc_info())	
		raise Exception('Failed to open file for simple switch test case scenario');
	
	

#This function validates the result of simple switch test case execution
def validateSimpleSwitchesTestCaseResults(fileName) :
	
	try :

		crossPointSuccessResponses= getCrossPointSuccessResponses(fileName);
		crossPointRequests= getCrossPointRequests(fileName);
	
		for sequence, request in crossPointRequests.iteritems() :
			print("RequestSwitch: seqNum: ", sequence, " crosspoint: ", request);
			print("CrosspointSuccess: seqNum",sequence, " crosspoint:", crossPointSuccessResponses[sequence]);	

			if crossPointSuccessResponses[sequence]['error'] != "0" or crossPointSuccessResponses[sequence]['srcId'] != request['srcId']  or crossPointSuccessResponses[sequence]['dstId'] != request['dstId']:
				print("Test Result: Failed");
				return;
					
		print("Test Result: Passed");
	except :
		print("Exception caught: ", sys.exc_info())
		print("Test Result: Failed");	


executeSimpleSwitchesTestCase()
validateSimpleSwitchesTestCaseResults('/home/dimitrios/Downloads/result.xml')
			
	   






	
	
	
