#Find all the worlds that containi an "a"
#cat sample.txt | rgrep a.* -n --colour 

#Find all the worlds that start with an "a" (the entire line must start with a)
#cat sample.txt | rgrep ^a.* -n --colour

#Find all the worlds that end with an "a"   (matches at the end of a line)
#cat sample.txt | rgrep a$ -n --colour

#Find all the worlds that match exactly abcd (the entire line must start with abcd)
#cat sample.txt | rgrep ^abcd$ -n --colour

#Find all the worlds that match exactly abcd, aabcd, aaabcd
#cat sample.txt | rgrep "^a\+bcd$" -n --colour

#Find all the worlds that match exactly abcd (xxxx abcd xxxx abcd)
#cat sample.txt | rgrep "\<abcd\>" -n --colour

# Find all the worlds that match this axcd abcd, afbcd e.t.c (b here is optional can be repeated at most once)
#cat sample.txt | rgrep "ab\?c." -n --colour

#Regular expression for matching IP address
#cat sample.txt | grep -w -n --color "\<\([0-9]\|[0-9][0-9]\|[0-2][0-5][0-5]\)\.\([0-9]\|[0-9][0-9]\|[0-2][0-5][0-5]\)\.\([0-9]\|[0-9][0-9]\|[0-2][0-5][0-5]\)\.\([0-9]\|[0-9][0-9]\|[0-2][0-5][0-5]$\)"

#Find all the users that they login with the bash as default
#cat /etc/passwd | grep  -w --color "/bin/bash"

# Find all the instances of x = 1, z =  12
#rgrep -E "[a-zA-Z0-9]+\s+=[^=]" ./ --colour

# Check that access time of a file is after 13:00 for the current directory
#data=`ls -al | grep -o -w --colour "[0-2][0-4]:[0-5][0-9]" | cut -d: -f1`
#for i in $data
#do
	#if [ $i -gt 13 ]
	#then
		#echo $i;
	#fi
#done

#Find all the empty lines in a file
# cat sample.txt | grep -v "^\s*$"

# Check for html tags like <html> Hi this is a website </html>
#cat sample.txt | grep --colour "<[a-zA-Z1-9\"= ]*>.*</\([a-zA-Z0-9]*\)>" 
