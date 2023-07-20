CXX = g++
CC = $(CXX)

CXXFLAGS = -std=c++17 -Wall -pedantic -g3
CXXFLAGS += -Werror

CPPFLAGS = -I ../includes -I ../src 
 
LDLIBS = -lgumbo -lcurl -lcurlpp 


main : ../src/text_client.o ../src/client_site.o ../src/proxy_searcher.o ../src/communicator.o
 
main.o : main.cpp  ../includes/text_client.hpp ../includes/client_site.hpp ../includes/proxy_searcher.hpp 


../src/client_site.o : ../src/client_site.cpp ../includes/client_site.hpp
../src/proxy_searcher.o : ../src/proxy_searcher.cpp ../includes/proxy_searcher.hpp ../includes/searcher.hpp ../includes/communicator.hpp
../src/text_client.o : ../src/text_client.cpp ../includes/text_client.hpp ../includes/text_client.hpp
../src/communicator.o : ../src/communicator.cpp ../includes/communicator.hpp

clean:
	$(RM) *.o ./main
