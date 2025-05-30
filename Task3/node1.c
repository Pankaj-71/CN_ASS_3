#include <stdio.h>
#include "nodeutil.h"

// extern struct rtpkt {
//   int sourceid;       /* id of sending router sending this pkt */
//   int destid;         /* id of router to which pkt being sent 
//                          (must be an immediate neighbor) */
//   int mincost[4];    /* min cost to node 0 ... 3 */
// };


extern int TRACE;
extern int YES;
extern int NO;

struct distance_table 
{
  int costs[4][4];
} dt1;

void printdt1(dtptr)
  struct distance_table *dtptr;
  
{
  printf("             via   \n");
  printf("   D1 |    0     2 \n");
  printf("  ----|-----------\n");
  printf("     0|  %3d   %3d\n",dtptr->costs[0][0], dtptr->costs[0][2]);
  printf("dest 2|  %3d   %3d\n",dtptr->costs[2][0], dtptr->costs[2][2]);
  printf("     3|  %3d   %3d\n",dtptr->costs[3][0], dtptr->costs[3][2]);

}

/* students to write the following two routines, and maybe some others */

#define SELFID 1
int mincost1[4] = {1, 0, 1, 999};

void rtinit1() 
{
  init_disttable(SELFID, (int *)dt1.costs, mincost1);
	updateneighbors(SELFID, mincost1, (int *)dt1.costs);
}


void rtupdate1(rcvdpkt)
  struct rtpkt *rcvdpkt;
  
{
	int mincost_updated = updatecosts(rcvdpkt, SELFID, mincost1, (int *)dt1.costs);
	printdt1(&dt1);	// print distance table

	if (mincost_updated)
	{
		updateneighbors(SELFID, mincost1, (int *)dt1.costs);
	}
}

/* called when cost from 1 to linkid changes from current value to newcost*/
/* You can leave this routine empty if you're an undergrad. If you want */
/* to use this routine, you'll need to change the value of the LINKCHANGE */
/* constant definition in prog3.c from 0 to 1 */
void linkhandler1(linkid, newcost)   
int linkid, newcost;   
{
  linkhandler(linkid, newcost, SELFID, mincost1, (int *)dt1.costs);
  printdt1(&dt1);	// print distance table
}
