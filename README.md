The Search Engine Project is a web crawling application crafted in C++, intended to scan internet
websites and archive the collected data into a MySQL database.
It empowers users with the ability to input search queries, and the application provides search 
results consisting of links containing the specified keywords. The links are sorted using the 
Pagerank algorithm, which ranks internet pages to prioritize the most relevant search results.
Additionally, the project supports receiving queries from remote users through the TCP protocol.
The project utilizes multithreading to enhance efficiency and enable concurrent searching and 
crawling, allowing users to search for information even while the crawling process is ongoing. 
It offers flexibility in its configuration options, allowing users to customize its behavior 
through a configuration file. Parameters such as scanning type (BFS or DFS), sorting method,
and client interface (local or remote) can be defined to tailor the application to specific 
preferences and requirements.

The main objects are Crawler and Search_engine.
The Crawler class is responsible for traversing web pages by retrieving URLs and parsing HTML content. 
It utilizes the Html_parser object to extract links and text from the retrieved pages. The extracted
data is then passed to the Updater class, which handles the insertion of data into the database.
The Updater class holds instances of classes that implement the Graph interface, representing the 
relationship between links, and the WordLinks interface, representing links that contain words.
The Crawler also interacts with instances of the Scanner interface, which can be configured for BFS 
or DFS strategies. Thread-safe sets are employed to ensure the uniqueness of URLs.
Additionally, the crawling process is controlled by the Limit_counter object, which stops the crawler 
when a specified limit of links is reached. The Limit_counter object is thread-safe, allowing for 
concurrent access and increases.

The Search_engine class is the application responsible for handling user queries, providing results,
and sorting outcomes. The Search_engine class achieves its tasks by holding three objects:
Client Interface: This object enables the Search_engine to receive queries from users. Whether the queries 
are entered locally via the console or remotely through sockets, the Search_engine efficiently manages 
user interactions.
Searcher Instance: The Search_engine utilizes an instance of the Searcher interface to retrieve relevant 
search results from a specific database.
Sorter Instance: Additionally, the Search_engine holds an instance of the Sorter interface to organize 
search results effectively. It can sort results either by word instances, the Pagerank algorithm, or any
other custom sorting method specified.
Additionally, injector implementations for Search_engine_injector and Crawler_injector to create tailored 
objects based on configuration file.
