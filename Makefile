CXX = g++
CC = $(CXX)

CXXFLAGS = -std=c++17 -Wall -pedantic -g3
CXXFLAGS += -Werror

CPPFLAGS = -I includes -I src 
 
LDLIBS = -lgumbo -lcurl -lcurlpp -lmysqlcppconn


main : main.o src/parser_html.o src/crawler.o src/extract_html.o \
src/link_maintenance_manager.o src/search_engine.o src/text_client.o  src/communicator.o \
src/regular_sorter.o src/socket.o src/net_client.o src/publisher.o \
src/updater.o src/threads.o src/configuration.o src/mysql_searcher.o src/mysql_links_rank_manager.o \
src/pageRank.o src/pr_sorter.o src/string_split.o src/safe_scores_map.o src/connector.o \
src/mysql_links_data.o src/mysql_graph_data.o src/mysql_word_data.o src/mysql_word_links.o src/safe_limit_counter.o

	$(CXX) $(LDFLAGS) $(CXXFLAGS) -o $@ $^ $(LDLIBS)


 
main.o : main.cpp includes/crawler.hpp\
includes/search_engine.hpp includes/text_client.hpp includes/net_client.hpp includes/updater.hpp includes/pageRank.hpp \
includes/mysql_links_data.hpp includes/connector.hpp includes/mysql_graph_data.hpp includes/searcher.hpp includes/mysql_links_rank_manager.hpp includes/pr_sorter.hpp includes/safe_limit_counter.hpp

src/parser_html.o : src/parser_html.cpp includes/parser_html.hpp includes/string_split.hpp
src/crawler.o : src/crawler.cpp includes/crawler.hpp includes/parser_html.hpp includes/extract_html.hpp  \
includes/se_exceptions.hpp includes/configuration.hpp includes/updater.hpp includes/safe_limit_counter.hpp includes/safe_scan.hpp

src/extract_html.o : src/extract_html.cpp includes/extract_html.hpp includes/se_exceptions.hpp
src/link_maintenance_manager.o : src/link_maintenance_manager.cpp includes/link_maintenance_manager.hpp 

src/search_engine.o : src/search_engine.cpp includes/search_engine.hpp includes/searcher.hpp 
src/net_client.o : src/net_client.cpp includes/net_client.hpp includes/client.hpp includes/socket.hpp includes/communicator.hpp includes/se_exceptions.hpp 
src/communicator.o : src/communicator.cpp includes/communicator.hpp includes/se_exceptions.hpp
src/socket.o : src/socket.cpp includes/socket.hpp includes/communicator.hpp includes/se_exceptions.hpp
src/regular_sorter.o : src/regular_sorter.cpp includes/regular_sorter.hpp
src/string_split.o : src/string_split.cpp includes/string_split.hpp
src/updater.o : src/updater.cpp includes/updater.hpp includes/publisher.hpp includes/safe_unordered_map.hpp includes/word_links.hpp includes/graph_data.hpp
src/pageRank.o : src/pageRank.cpp includes/pageRank.hpp
src/pr_sorter.o : src/pr_sorter.cpp includes/pr_sorter.hpp includes/pageRank.hpp
src/configuration.o : src/configuration.cpp includes/configuration.hpp
src/connector.o : src/connector.cpp includes/connector.hpp
src/mysql_links_data.o : src/mysql_links_data.cpp includes/mysql_links_data.hpp includes/links_data.hpp
src/mysql_graph_data.o : src/mysql_graph_data.cpp includes/mysql_graph_data.hpp includes/graph_data.hpp
src/mysql_word_data.0 : src/mysql_word_data.cpp includes/mysql_word_data.hpp includes/word_data.hpp
src/mysql_word_links.o : src/mysql_word_links.cpp includes/mysql_word_links.hpp includes/word_links.hpp
src/mysql_searcher.o : src/mysql_searcher.cpp includes/mysql_searcher.hpp includes/searcher.hpp
src/mysql_links_rank_manager.o : src/mysql_links_rank_manager.cpp includes/mysql_links_rank_manager.hpp includes/links_rank_manager.hpp includes/safe_scores_map.hpp includes/mysql_graph_data.hpp
src/publisher.o : src/publisher.cpp includes/publisher.hpp includes/links_rank_manager.hpp 
src/threads.o : src/threads.cpp includes/threads.hpp src/configuration.cpp
src/safe_limit_counter.o : includes/safe_limit_counter.hpp src/safe_limit_counter.cpp 

clean:
	$(RM) *.o ./main src/*.o