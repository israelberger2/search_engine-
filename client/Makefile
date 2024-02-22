CXX = g++
CC = $(CXX)

CXXFLAGS = -std=c++17 -Wall -pedantic -g3
CXXFLAGS += -Werror

CPPFLAGS = -I ../includes -I ../src -I ..
 
LDLIBS = -lgumbo -lcurl -lcurlpp 


main : ../src/text_client.o client_site.o network_handler.o ../src/communicator.o 
 
main.o : main.cpp  ../includes/text_client.hpp client_site.hpp network_handler.hpp 


client_site.o : client_site.cpp client_site.hpp
network_handler.o : network_handler.cpp network_handler.hpp ../includes/communicator.hpp ../includes/configuration.hpp
../src/text_client.o : ../src/text_client.cpp ../includes/text_client.hpp ../includes/text_client.hpp
../src/communicator.o : ../src/communicator.cpp ../includes/communicator.hpp

clean:
	$(RM) *.o ./main
