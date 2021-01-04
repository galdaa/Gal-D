/*********************************************************
ESCRIPTION: Implement functions of UID.
Athor: Gal Dahan
Reviewer: Ronny Efronny
**********************************************************/

#include <unistd.h>  	 /* pid_t */
#include "uid.h"

ilrd_uid_t UIDCreate(void)
{
	ilrd_uid_t new_uid = {0};
	
	static pid_t pid_counter = 1;
	
	new_uid.timestamp = time(NULL);
	
	if(-1 == new_uid.timestamp)
	{
		return UIDGetBadUid();
	}
	
	new_uid.pid = getpid();
	new_uid.counter = pid_counter;
	++pid_counter;
	
	return new_uid;
}

int UIDIsSame(ilrd_uid_t lhs, ilrd_uid_t rhs)
{
	int flag = 1;
	
	if(lhs.timestamp != rhs.timestamp)
	{
		flag = 0;
	}
	else if(lhs.pid != rhs.pid)
	{
		flag = 0;
	}
	else if(lhs.counter != rhs.counter)
	{
		flag = 0;
	}
	
	return flag;
}

ilrd_uid_t UIDGetBadUid(void)
{
	ilrd_uid_t bad_uid = {0};
	
	bad_uid.timestamp = 0;
	bad_uid.pid = 0;
	bad_uid.counter = 0;
	
	return bad_uid;
}
