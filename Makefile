CXX = g++
CC = $(CXX)

CXXFLAGS = -std=c++17 -Wall -pedantic -g3
CXXFLAGS += -Werror

CPPFLAGS = -I includes -I src -I db/includes -I db/src
 
LDLIBS = -lgumbo -lcurl -lcurlpp -lmysqlcppconn


main : main.o src/parser_html.o src/crawler.o src/extract_html.o \
src/link_maintenance_manager.o src/search_engine.o src/text_client.o  src/communicator.o \
src/word_instance_sorter.o src/socket.o src/net_client.o src/publisher.o \
src/updater.o src/threads.o src/configuration.o db/src/mysql_searcher.o db/src/links_rank_manager.o \
src/pageRank.o src/pagerank_sorter.o src/string_split.o src/safe_scores_map.o src/connector.o \
db/src/mysql_links_data.o db/src/mysql_graph_data.o db/src/mysql_word_data.o db/src/mysql_word_links.o src/safe_limit_counter.o src/crawler_injector.o src/search_engine_injector.o

main.o : main.cpp includes/crawler.hpp includes/se_exceptions.hpp includes/crawler_injector.hpp \
includes/safe_scores_map.hpp includes/configuration.hpp includes/search_engine.hpp includes/search_engine_injector.hpp


src/search_engine_injector.o : src/search_engine_injector.cpp includes/search_engine_injector.hpp includes/safe_scores_map.hpp \
includes/pagerank_sorter.hpp includes/word_instance_sorter.hpp db/includes/mysql_searcher.hpp includes/configuration.hpp includes/net_client.hpp includes/text_client.hpp
 
src/crawler_injector.o : src/crawler_injector.cpp includes/crawler_injector.hpp includes/safe_scores_map.hpp includes/crawler.hpp \
db/includes/links_rank_manager.hpp includes/updater.hpp db/includes/mysql_graph_data.hpp db/includes/mysql_word_links.hpp \
includes/configuration.hpp includes/dfs.hpp includes/bfs.hpp

src/parser_html.o : src/parser_html.cpp includes/parser_html.hpp includes/string_split.hpp
src/crawler.o : src/crawler.cpp includes/crawler.hpp includes/parser_html.hpp includes/extract_html.hpp includes/threads.hpp \
includes/se_exceptions.hpp includes/configuration.hpp includes/updater.hpp includes/safe_limit_counter.hpp includes/safe_scan.hpp

src/extract_html.o : src/extract_html.cpp includes/extract_html.hpp includes/se_exceptions.hpp
src/link_maintenance_manager.o : src/link_maintenance_manager.cpp includes/link_maintenance_manager.hpp 

src/search_engine.o : src/search_engine.cpp includes/search_engine.hpp includes/searcher.hpp 
src/net_client.o : src/net_client.cpp includes/net_client.hpp includes/client.hpp includes/socket.hpp includes/communicator.hpp includes/se_exceptions.hpp 
src/communicator.o : src/communicator.cpp includes/communicator.hpp includes/se_exceptions.hpp
src/socket.o : src/socket.cpp includes/socket.hpp includes/communicator.hpp includes/se_exceptions.hpp
src/word_instance_sorter.o : src/word_instance_sorter.cpp includes/word_instance_sorter.hpp
src/string_split.o : src/string_split.cpp includes/string_split.hpp
src/updater.o : src/updater.cpp includes/updater.hpp includes/publisher.hpp includes/safe_unordered_map.hpp includes/word_links.hpp includes/graph_data.hpp
src/pageRank.o : src/pageRank.cpp includes/pageRank.hpp
src/pagerank_sorter.o : src/pagerank_sorter.cpp includes/pagerank_sorter.hpp includes/pageRank.hpp
src/configuration.o : src/configuration.cpp includes/configuration.hpp
src/connector.o : src/connector.cpp includes/connector.hpp
db/src/mysql_links_data.o : db/src/mysql_links_data.cpp db/includes/mysql_links_data.hpp db/includes/links_data.hpp
db/src/mysql_graph_data.o : db/src/mysql_graph_data.cpp db/includes/mysql_graph_data.hpp includes/graph_data.hpp
db/src/mysql_word_data.0 : db/src/mysql_word_data.cpp db/includes/mysql_word_data.hpp includes/word_data.hpp
db/src/mysql_word_links.o : db/src/mysql_word_links.cpp db/includes/mysql_word_links.hpp includes/word_links.hpp
db/src/mysql_searcher.o : db/src/mysql_searcher.cpp db/includes/mysql_searcher.hpp includes/searcher.hpp
db/src/links_rank_manager.o : db/src/links_rank_manager.cpp db/includes/links_rank_manager.hpp includes/subscriber.hpp includes/safe_scores_map.hpp db/includes/mysql_graph_data.hpp
src/publisher.o : src/publisher.cpp includes/publisher.hpp includes/subscriber.hpp 
src/threads.o : src/threads.cpp includes/threads.hpp src/configuration.cpp
src/safe_limit_counter.o : src/safe_limit_counter.cpp  includes/safe_limit_counter.hpp
 
 
clean:
	$(RM) *.o ./main src/*.o