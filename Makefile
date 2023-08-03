CXX = g++
CC = $(CXX)

CXXFLAGS = -std=c++17 -Wall -pedantic -g3
CXXFLAGS += -Werror

CPPFLAGS = -I includes -I src 
 
LDLIBS = -lgumbo -lcurl -lcurlpp -lmysqlcppconn


main : main.o src/parser_html.o src/links_map.o src/indexer.o src/crawler.o src/database.o src/extract_html.o \
src/reg_algo_links_maintenance.o src/search_engine.o src/text_client.o  src/communicator.o \
src/regular_sorter.o src/border_manager.o src/acceptor.o src/net_client.o src/publisher.o \
src/updater.o src/threads.o src/configuration.o src/searcher.o \
src/pageRank.o src/pr_sorter.o src/string_split.o  src/safe_scores_map.o src/pagerank_scheduler.o src/connector.o \
src/link.o src/mysql_links_data.o src/mysql_domain_data.o src/mysql_graph_data.o src/mysql_word_data.o src/mysql_word_links.o

	$(CXX) $(LDFLAGS) $(CXXFLAGS) -o $@ $^ $(LDLIBS)


 
main.o : main.cpp  includes/crawler.hpp includes/indexer.hpp includes/links_map.hpp includes/database.hpp \
includes/search_engine.hpp includes/text_client.hpp includes/net_client.hpp includes/updater.hpp includes/pageRank.hpp \
includes/mysql_links_data.hpp includes/connector.hpp includes/mysql_domain_data.hpp includes/mysql_graph_data.hpp includes/searcher.hpp

src/parser_html.o : src/parser_html.cpp includes/parser_html.hpp includes/links_maintenance.hpp includes/string_split.hpp
src/links_map.o : src/links_map.cpp includes/links_map.hpp includes/links_map_insertion.hpp includes/links_map_get.hpp
src/indexer.o : src/indexer.cpp includes/indexer.hpp includes/indexer_insertion.hpp includes/indexer_get.hpp
src/crawler.o : src/crawler.cpp includes/crawler.hpp includes/parser_html.hpp includes/extract_html.hpp  \
includes/reg_algo_links_maintenance.hpp includes/se_exceptions.hpp includes/configuration.hpp includes/updater.hpp

src/database.o : src/database.cpp includes/database.hpp includes/indexer_get.hpp includes/links_map_get.hpp
src/extract_html.o : src/extract_html.cpp includes/extract_html.hpp includes/se_exceptions.hpp
src/reg_algo_links_maintenance.o : src/reg_algo_links_maintenance.cpp includes/reg_algo_links_maintenance.hpp \
includes/links_maintenance.hpp

src/search_engine.o : src/search_engine.cpp includes/search_engine.hpp includes/searcher.hpp includes/database.hpp
# src/factory_searcher.o : src/factory_searcher.cpp includes/factory_searcher.hpp includes/exist_and_unexist_search.hpp includes/exist_words_search.hpp includes/unexist_words_search.hpp
# src/exist_words_search.o : src/exist_words_search.cpp includes/exist_words_search.hpp includes/searcher.hpp
# src/unexist_words_search.o : src/unexist_words_search.cpp includes/unexist_words_search.hpp includes/searcher.hpp
# src/exist_and_unexist_search.o : src/exist_and_unexist_search.cpp includes/exist_and_unexist_search.hpp includes/searcher.hpp
src/text_client.o : src/text_client.cpp includes/text_client.hpp includes/text_client.hpp
src/net_client.o : src/net_client.cpp includes/net_client.hpp
src/communicator.o : src/communicator.cpp includes/communicator.hpp includes/se_exceptions.hpp
src/acceptor.o : src/acceptor.cpp includes/acceptor.hpp includes/communicator.hpp
src/regular_sorter.o : src/regular_sorter.cpp includes/regular_sorter.hpp
src/string_split.o : src/string_split.cpp includes/string_split.hpp
src/updater.o : src/updater.cpp includes/updater.hpp includes/links_map.hpp includes/indexer.hpp
src/pageRank.o : src/pageRank.cpp includes/pageRank.hpp includes/links_map.hpp
src/pr_sorter.o : src/pr_sorter.cpp includes/pr_sorter.hpp includes/pageRank.hpp
src/border_manager.o : src/border_manager.cpp includes/border_manager.hpp
src/configuration.o : src/configuration.cpp includes/configuration.hpp
src/connector.o : src/connector.cpp includes/connector.hpp
src/link.o : src/link.cpp includes/link.hpp
src/mysql_links_data.o : src/mysql_links_data.cpp includes/mysql_links_data.hpp includes/links_data.hpp
src/mysql_domain_data.o : src/mysql_domain_data.cpp includes/mysql_domain_data.hpp includes/domain_data.hpp
src/mysql_graph_data.o : src/mysql_graph_data.cpp includes/mysql_graph_data.hpp includes/graph_data.hpp
src/mysql_word_data.0 : src/mysql_word_data.cpp includes/mysql_word_data.hpp includes/word_data.hpp
src/mysql_word_links.o : src/mysql_word_links.cpp includes/mysql_word_links.hpp includes/word_links.hpp


clean:
	$(RM) *.o ./main src/*.o