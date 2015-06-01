# EXAMPLE NUMBER 1. Find all the source files and replace hal_handle_t hal, or hal_handle_t hal, or hal_handle_t hal , with a space

#SOURCE_FILES=`find -iname "*.c" -o -iname "*.cpp" -o -iname "*.h"`

#for i in $SOURCE_FILES
#do
#cat ${i} | sed 's/\(hal_handle_t\shal,\)\|\(hal_handle_t\shal\)\|\(hal_handle_t\shal,\s\)//' > tmp && mv tmp ${i}
#done

# EXAMPLE 2: tonight is a wonderful day in the park (only the first occurance will be changed per line)
#echo today is a wonderful day in the park | sed 's/day/night/' 

# EXAMPLE 3: echo today is a wonderful day in the park (123)
#echo today is a wonderful day in the park 123 | sed 's/[1-9]\+/(&)/'

# EXAMPLE 4: abcd it will match only the first part of the match pattern
#echo abcd123 | sed 's/\([a-z]*\).*/\1/'

# EXAMPLE 5: name skata (\1 matches exactly what [a-z]* matches which is name) so it removes the second name
# echo name name skata | sed -E 's/([a-z]*) \1/\1/'

# EXAMPLE 6: This will print (this is a duplicate duplicate world) p means print it and \1 is the first matched pattern
# cat sample.txt | sed -rn '/(\<[a-z]+\>) \1/p'

# EXAMPLE 7: This will print any douplicate found in a line
# cat sample.txt | sed -rn '/(\<[a-z]+\>)(.*)\1/p'

# EXAMPLE 8: This will replace every world in a line by () Result: (Hello) (My) (Dear) (Friend)
# echo Hello My Dear Friend | sed -r 's/[^ ]+/(&)/g'

# EXAMPLE 9: This will find and replace only the second match pattern Result: First DELETE Third Forth Fifth
# echo First Second Third Forth Fifth| sed 's/[a-zA-Z]* /DELETE /2

#EXAMPLE 10: This will find an expression of this form x = 1, y   =  1; and delete the space and the output would be of this form x= 1
#cat sample.txt | sed -E '/[a-zA-Z0-9]+\s+=[^=]/ s/\s+//''

#EXAMPLE 11: This will find the world Operator in the end of a line. Once found it will read the second line and try to to pattern matching on two lines
#cat sample.txt | sed -E '/Operator/ {N; s/Owner and Operator\nGuide/Installation Guide/ }'

#EXAMPLE 12: Find the # symbol and read the next line. If the next line is just the new line then delete it
#cat sample.txt | sed -E '/#$/ {N; s/\n$// }'


