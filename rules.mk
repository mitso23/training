DIR:=$(PRJ_ROOT)/$(DIR)

SRCS:= $(patsubst %,$(DIR)/%,$(SRCS))

ifneq (,$(findstring g++,$(CC)))
	OBJS:= $(patsubst %.cpp,%.o,$(SRCS))
else
	OBJS:= $(patsubst %.c,%.o,$(SRCS))
endif

ifneq (,$(findstring .so,$(NAME)))
	OUTDIR:=$(PRJ_ROOT)/lib/$(NAME)
else
	OUTDIR:=$(PRJ_ROOT)/bin/$(NAME)
endif

$(NAME) : $(OBJS)
	$(CC) $(OBJS) $(LDFLAGS) $(LIBS) -o $(OUTDIR) 

$(DIR)/%.o: $(DIR)/%.cpp
	$(CC) -c $(CFLAGS) $(INCLUDES) -c $< -o $@

$(DIR)/%.o: $(DIR)/%.c
	$(CC) -c $(CFLAGS) $(INCLUDES) -c $< -o $@

depend: $(SRCS)
	makedepend -f ${PRJ_ROOT}/rules.mk -- $(SRCS) -I ${PRJ_ROOT}/include -Y > /dev/null 2>&1  

clean:
ifeq (,$(findstring .so,$(NAME)))
	$(RM) $(DIR)/*.o $(PRJ_ROOT)/bin/$(NAME) 
else
	$(RM) $(DIR)/*.o $(DIR)/*.so $(PRJ_ROOT)/lib/$(NAME)
endif
# DO NOT DELETE

/home/mitso23/training//testapps/Algorithms/algorithms.o: /home/mitso23/training/testapps/Algorithms/Stl/stl.h
/home/mitso23/training//testapps/Algorithms/algorithms.o: /home/mitso23/training/testapps/Algorithms/dynamic_programming/coin_changing_problem.h
/home/mitso23/training//testapps/Algorithms/algorithms.o: /home/mitso23/training/testapps/Algorithms/sorting/mergeSort.h
/home/mitso23/training//testapps/Algorithms/algorithms.o: /home/mitso23/training/testapps/Algorithms/backtracking/labyrinth_wall.h
/home/mitso23/training//testapps/Algorithms/algorithms.o: /home/mitso23/training/testapps/Algorithms/combinatronics/permutation.h
/home/mitso23/training//testapps/Algorithms/algorithms.o: /home/mitso23/training/testapps/Algorithms/backtracking/collect_max_points_before_hitting_dead_end.h
/home/mitso23/training//testapps/Algorithms/algorithms.o: /home/mitso23/training/testapps/Algorithms/recursion/sum_digits.h
/home/mitso23/training//testapps/Algorithms/algorithms.o: /home/mitso23/training/testapps/Algorithms/combinatronics/combination_k_out_of_n_items.h
/home/mitso23/training//testapps/Algorithms/algorithms.o: /home/mitso23/training/testapps/Algorithms/linklist/list.h
/home/mitso23/training//testapps/Algorithms/algorithms.o: /home/mitso23/training/testapps/Algorithms/parsers/matching_brackets.h
/home/mitso23/training//testapps/Algorithms/algorithms.o: /home/mitso23/training/testapps/Algorithms/graphs/graph.h
/home/mitso23/training//testapps/Algorithms/algorithms.o: /home/mitso23/training/testapps/Algorithms/matrix/communication_stations.h
/home/mitso23/training//testapps/Algorithms/algorithms.o: /home/mitso23/training/testapps/Algorithms/backtracking/rat_in_a_maze.h
/home/mitso23/training//testapps/Algorithms/algorithms.o: /home/mitso23/training/testapps/Algorithms/recursion/num_ways_to_reach_stairs.h
/home/mitso23/training//testapps/Algorithms/algorithms.o: /home/mitso23/training/testapps/Algorithms/backtracking/min_cost_in_matrix.h
/home/mitso23/training//testapps/Algorithms/algorithms.o: /home/mitso23/training/testapps/Algorithms/linklist/list.h
/home/mitso23/training//testapps/Algorithms/algorithms.o: /home/mitso23/training/testapps/Algorithms/backtracking/N-Queen-Problem.h
/home/mitso23/training//testapps/Algorithms/algorithms.o: /home/mitso23/training/testapps/Algorithms/backtracking/HourGlassBacktracking.h
/home/mitso23/training//testapps/Algorithms/algorithms.o: /home/mitso23/training/testapps/Algorithms/combinatronics/combination.h
/home/mitso23/training//testapps/Algorithms/algorithms.o: /home/mitso23/training/testapps/Algorithms/dynamic_programming/binominal_coefficents.h
/home/mitso23/training//testapps/Algorithms/algorithms.o: /home/mitso23/training/testapps/Algorithms/dynamic_programming/paintfence_algorithm.h
/home/mitso23/training//testapps/Algorithms/algorithms.o: /home/mitso23/training/testapps/Algorithms/combinatronics/Knapsack.h
/home/mitso23/training//testapps/Algorithms/algorithms.o: /home/mitso23/training/testapps/Algorithms/backtracking/fillCanvas.h
/home/mitso23/training//testapps/Algorithms/algorithms.o: /home/mitso23/training/testapps/Algorithms/backtracking/WordBreaking.h
/home/mitso23/training//testapps/Algorithms/algorithms.o: /home/mitso23/training/testapps/Algorithms/backtracking/longest_path_hurdels.h
/home/mitso23/training//testapps/Algorithms/algorithms.o: /home/mitso23/training/testapps/Algorithms/combinatronics/numberofPossibleScores.h
/home/mitso23/training//testapps/Algorithms/algorithms.o: /home/mitso23/training/testapps/Algorithms/backtracking/find_path_magic_triangle.h
/home/mitso23/training//testapps/Algorithms/algorithms.o: /home/mitso23/training/testapps/Algorithms/backtracking/escape_from_room.h
/home/mitso23/training//testapps/Algorithms/algorithms.o: /home/mitso23/training/testapps/Algorithms/backtracking/pattern_matching.h
/home/mitso23/training//testapps/Algorithms/algorithms.o: /home/mitso23/training/testapps/Algorithms/dynamic_programming/longest_common_subsequence.h
/home/mitso23/training//testapps/Algorithms/algorithms.o: /home/mitso23/training/testapps/Algorithms/backtracking/max_non_parallel_lines.h
/home/mitso23/training//testapps/Algorithms/algorithms.o: /home/mitso23/training/testapps/Algorithms/backtracking/max_bins_2d_array.h
/home/mitso23/training//testapps/Algorithms/algorithms.o: /home/mitso23/training/testapps/Algorithms/recursion/numers_have_four_digit.h
/home/mitso23/training//testapps/Algorithms/algorithms.o: /home/mitso23/training/testapps/Algorithms/graphs/shortest_path_graph_naive.h
/home/mitso23/training//testapps/Algorithms/algorithms.o: /home/mitso23/training/testapps/Algorithms/backtracking/find_edge_picture.h
/home/mitso23/training//testapps/Algorithms/algorithms.o: /home/mitso23/training/testapps/Algorithms/graphs/shortest_path_warmhole.h
/home/mitso23/training//testapps/Algorithms/algorithms.o: /home/mitso23/training/testapps/Algorithms/sorting/warmhole_contest.h
/home/mitso23/training//testapps/Algorithms/algorithms.o: /home/mitso23/training/testapps/Algorithms/image_processing/k_means_algorithm.h
/home/mitso23/training//testapps/Algorithms/algorithms.o: /home/mitso23/training/testapps/Algorithms/graphs/shortest_path_floyd.h
/home/mitso23/training//testapps/Algorithms/algorithms.o: /home/mitso23/training/testapps/Algorithms/trees/tree.h
/home/mitso23/training//testapps/Algorithms/algorithms.o: /home/mitso23/training/testapps/Algorithms/trees/check_tree_balanced.h
/home/mitso23/training//testapps/Algorithms/algorithms.o: /home/mitso23/training/testapps/Algorithms/trees/tree.h
/home/mitso23/training//testapps/Algorithms/algorithms.o: /home/mitso23/training/testapps/Algorithms/graphs/union_find_detect_circle.h
/home/mitso23/training//testapps/Algorithms/algorithms.o: /home/mitso23/training/testapps/Algorithms/graphs/graph.h
/home/mitso23/training//testapps/Algorithms/algorithms.o: /home/mitso23/training/testapps/Algorithms/graphs/graph_mst_prime.h
/home/mitso23/training//testapps/Algorithms/algorithms.o: /home/mitso23/training/testapps/Algorithms/graphs/topological_sort.h
/home/mitso23/training//testapps/Algorithms/algorithms.o: /home/mitso23/training/testapps/Algorithms/trees/convert_bst_sum_tree.h
/home/mitso23/training//testapps/Algorithms/algorithms.o: /home/mitso23/training/testapps/Algorithms/graphs/boggle.h
/home/mitso23/training//testapps/Algorithms/algorithms.o: /home/mitso23/training/testapps/Algorithms/graphs/find_articulation_point.h
/home/mitso23/training//testapps/Algorithms/algorithms.o: /home/mitso23/training/testapps/Algorithms/trees/find_minimum_height_binary_tree.h
/home/mitso23/training//testapps/Algorithms/algorithms.o: /home/mitso23/training/testapps/Algorithms/trees/find_common_anchestor.h
/home/mitso23/training//testapps/Algorithms/algorithms.o: /home/mitso23/training/testapps/Algorithms/trees/find_distance_between_two_nodes.h
