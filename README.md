# Information Retrieval (‘Search Engine’) Program
I developed a document retrieval system using the C programming language. Its main purpose is to search through a collection of documents and determine how relevant they are to a given query. The system performs this task efficiently, ensuring quick responses to users' requests for information.

One of the key features of the system is its ability to evaluate the connection between the query and the content of the documents. This assessment allows the system to filter out irrelevant information and present users with accurate results, saving them time and effort in finding the data they need. The use of C programming was instrumental in creating this sophisticated solution, as it enabled me to optimize the search process and ensure that the system runs smoothly and effectively. Overall, the document retrieval system proves to be a valuable tool for anyone seeking fast and reliable access to relevant information from a vast collection of documents.

# Additional Information
In this project, all the specified requirements were successfully met. A hashmap was implemented, utilizing a list of lists to store the data. The necessary functions, including hash_code, hash_table_insert, training function, read_query, rank function, and stop_word, were all implemented within the function.c and hashmap.c files. These functions have been thoroughly tested to ensure their proper functionality across various test cases.

To ensure ease of use and execution, a functional make file was provided, and the program was compiled on the shell. The program could be executed via a search command. However, one assumption made during development was that user-entered strings would contain 20 words or less, as permitted by the guidelines outlined in section 3.1 Assumptions and Requirements.

Notably, the program was designed to display results with increased decimal precision, contributing to more accurate document scores. The hash_table_insert function facilitated the insertion of words alongside their corresponding document information into the hashmap. The training function was responsible for reading and processing documents, adding relevant words to the hashmap, and removing stop words. On the other hand, the read_query function was responsible for processing user queries and calling the rank function to rank the document scores accordingly.

An additional feature was incorporated into the program to handle invalid input regarding the number of buckets. If the user provided an invalid input, such as a letter or a value less than 0, the program would promptly inform the user of the error and prompt them to re-enter the correct input. It's worth noting that the hashmap used in the program was a doubly linked list.

Skills: C (Programming Language)
