# Search for files under /usr/lib and /usr/src for patterns *.c and *.h and *.so and pipe the result to less
# -iname is case insensitive
# find /usr/lib/ /usr/src -iname *.c -o -iname *.h -o -iname *.so | less

# Search for files under /usr/lib/google or /usr/lib/skata/hese but not /usr/lib
# find /usr/lib/ -mindepth 1 -iname *.so

# Search for files only under /usr/lib/ and not /usr/lib/hese
# find /usr/lib/ -maxdepth 1 -iname *.so

# Find file that has been accessed less than a minute ago
# find ./ -amin 1

# Find a file that has been accessed earlier that regex
#find ./ -anewer regex.sh

# Find all the symbolic link files in /usr/lib 
# find /usr/lib/ -maxdepth 1 -lname "*" | xargs ls -al

# Find all the names that contain ./sample* (parses the entire full name including the directory name)
# find ./ -path "./sample*"

# Find all the names that don't include example* or rege*
# find ./ ! -iname "sample*" -and ! -name "rege*"

# Find all the names in the current directory and do a full listing
# find . -type f -exec ls -al '{}' ";"

# Find all the files that the owner can read and the group can write
# find . -type f -perm /u=r -and -perm /g=w

# Find all the *.txt files and put their detail to temp.txt and find all the *.sh files and put them to the temp.sh
#find ./ \( -name "*.txt" -fprintf temp.txt "mode:%#m,user:%u,%p\n" \) -o \( -name "*.sh" -fprintf temp.sh "mode:%#m,user:%u,%p\n" \)

# Find all the *.txt files in the current directory and /etc excluding tesetDir
# find ./ /etc/ -iname testDir -prune -o -iname "*.txt" -print

# Find the files and do a full listing
#ls -l `find . -print`
