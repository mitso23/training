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
