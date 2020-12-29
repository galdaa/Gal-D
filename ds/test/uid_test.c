/*********************************************************
ESCRIPTION: Test functions on UID.
Athor: Gal Dahan
Reviewer:---
**********************************************************/

#include <stdio.h>/*printf*/
#include "tests.h"
#include "uid.h"

void Test(void);

int main()
{
	Test();
	return 0;
}

void Test(void)
{
	ilrd_uid_t uid1 = UIDCreate();
	ilrd_uid_t uid2 = UIDCreate();

	printf("UIDCreate Sucsses  (not crashed)\n");

	printf("===Stage 1===\n");

	TEST("UIDIsSame", UIDIsSame(uid1, uid2), 0);
	
	UIDGetBadUid();
	printf("UIDGetBadUid Sucsses  (not crashed)\n");

	printf("===Stage 2===\n");
	
	TEST("UIDIsSame-UIDGetBadUid", UIDIsSame(UIDGetBadUid(), UIDGetBadUid()), 1);
	TEST("UIDCreate-UIDGetBadUid", UIDIsSame(UIDGetBadUid(), uid1), 0);
}

