#include "SubscriberHelper.h"

void PrintSubsriberMenu(Topic_node** head, int counter)
{
	printf("\n\n-----------------------Menu---------------------\n");
	printf("Subsribe to specific topic\n");
	PrintTopicListWithCounter(head);
	printf("%d. Finished with subscribing\n", counter+1);
}

int SubscribeToSpecificTopic(int topicCounter, int* subscribedTopics)
{
	int option = -1;

	if (topicCounter == 0)
	{
		printf("\nThere are no topics!\n");
		return -1;
	}

	do {

		printf("Select topic to subscribe: ");
		scanf("%d", &option);

		if (subscribedTopics[option - 1] == 1)
			printf("\nYou are already subscribed to selected topic!\n");

	} while (!ValidateSubscriberInput(option, topicCounter));

	return option;
}

bool ValidateSubscriberInput(int selectedOption, int topicCounter)
{
	bool condition = (selectedOption < 1 || selectedOption > topicCounter + 1) ? false : true;

	if (!condition)
	{
		if (topicCounter == 1)
			printf("\nYou can not select %d., try with option 1.\n", selectedOption);
		else
			printf("\nYou can not select %d., try with option beetween 1. and %d.\n", selectedOption, topicCounter + 1);
	}

	return condition;

}


bool SubscribedToAllTopics(int *subscribedTopics, int topicCounter)
{
	int i = 0;

	for (i = 0; i < topicCounter; i++)
	{
		if (subscribedTopics[i] == 0)
			return true;

	}

	return false;
}



void PrintSubsribedTopics(Topic_node** head, int *subscribedTopics, int topicCounter)
{

	

	printf("\n*****************************************************************\n");
	printf("Subsribed to next topics: ");

	for (int i = 0; i < topicCounter; i++)
	{
		if (subscribedTopics[i] == 1)
		{
			//subsribedTo = FindElementByIdTopicList(head, i);
			//printf("%s, ", subsribedTo->topic);
			char* topic = (FindTopicByIdTopicList(head, i));
			char TopicName[7];
			char Value[4];

			strncpy(TopicName, topic, 6);
			TopicName[6] = '\0'; // Null-terminate the TopicName


			strncpy(Value, topic + 6, 3);

			Value[3] = '\0';
			printf("%s-%s, ",TopicName, Value);

		}
	}

	printf("\n*****************************************************************\n\n");


}

/*
void ThreadRecieveFunction(Topic_node **head, SOCKET connectSocket, char* recvbuf)
{
	SelectFunction(connectSocket, READ);
	RecieveServerMessage(head, connectSocket, recvbuf, DEFAULT_BUFLEN);
}

*/

DWORD WINAPI ThreadRecieveFunction(LPVOID lpvThreadParam)
{

	Important_data *importantData = (Important_data*)lpvThreadParam;

	SOCKET connectSocket = importantData->connectSocket;
	Topic_node **head = importantData->head;
	
	free(lpvThreadParam);  

	char recvbuf[DEFAULT_BUFLEN];

	

	printf("\n\n----------------------------------------------------------------\n");
	printf("Waiting for news from publisher..\n\n");

	SelectFunction(connectSocket, READ);
	RecieveServerMessage(head, connectSocket, recvbuf);


	return 0;
}


