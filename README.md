/*CSci4061 Assignment 3
* name: Cuiqing Li, full name2 (for partner)
* id: 5028341, x500_2*/

Description of my codes:
   In my program, firstly I need to store all the data in the TwitterDb.txt in a struct array named as twitterarray[26]. Then, I need to open file named as client1.in,client2.in,client3.in or client4.in to red data. Since my queue has a max capacity which is the value of num_threads in the assignment question, so I can only pass the first num_threads elements in the client.in file into my queue data structure. Then, I use two child threading functions to handle the next problem. Produce function is used to add new elements (clients' string values) into the queue structure,and the consume function is used to extract elements from the queue structure. If the queuelength()'s value is equal to the max capacity of the queue, then we need to use function pthread_cond_wait() to wait for signal from consume function, otherwise we can just add new elements into the queue without worrying about anything. However, if the consume function finds that queuelength()==0, there are two cases. Case 1: we have read all the clients' string into the queue, and no other data is left. In this case, the consume function will wait a signal from the produce function to exit. Case 1: if we still haven't read all the data from the client.in file, then the consume function need to wait for produce function to add new elements into the queue structure. After that, the produce will send a signal to consume function to continue to extract data from the queue. Hence, using this method can finnally finish all the tasks.   