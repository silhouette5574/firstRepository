#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>

typedef struct point2d {
	int x,y;
} point2d;

/*struct point3d {
	int x,y,z;
};*/

void closestpair2d(struct point2d *, int);
//void closestpair3d(struct point3d *,struct point3d *,int);
//void euclideanMST(struct point2d **,struct point2d *,int);

int compareX(const void* a, const void* b){
	printf("IN COMPARE X\n");
	point2d *p1 = (point2d *)a;
	point2d *p2 = (point2d *)b;
	return (p1 -> x - p2 -> x);
}

int compareY(const void* a, const void* b){
        printf("IN COMPARE Y\n");
	point2d *p1 = (point2d *)a;
        point2d *p2 = (point2d *)b;
        return (p1 -> y - p2 -> y);
}

float dist(point2d p1, point2d p2){
	printf("IN DIST\n");
	return sqrt((p1.x-p2.x)*(p1.x-p2.x) + (p1.y-p2.y)*(p1.y-p2.y));
}

float bruteforce(point2d points[], int n){
	printf("IN BRUTEFORCE\n");
	float min = FLT_MAX;
	int i, j;
	for (i = 0; i < n; ++i)
        	for (j = i+1; j < n; ++j)
        		if (dist(points[i], points[j]) < min)
                		min = dist(points[i], points[j]);
	return min;
}

float minimum(float x, float y){
	printf("IN MINIMUM\n");
	if(x < y)
		return x;
	else
		return y;
}

float stripClosest(point2d strip[], int size, float d){
	printf("IN STRIP CLOSEST\n");
	float min = d;
	qsort(strip, size, sizeof(point2d), compareY);
	
	int i, j;
	for(i = 0; i < size; i++)
		for(j = i+1; j < size && (strip[j].y - strip[i].y < min); j++)
			if(dist(strip[i], strip[j]) < min)
				min = dist(strip[i], strip[j]);
	return min;
}

float closestUtil(point2d points[], int n){
	printf("IN CLOSEST UTIL 2d\n");
	if(n <= 3)
		return bruteforce(points, n);
	
	int mid = n/2;
	point2d midpoint = points[mid];

	float dl = closestUtil(points, mid);
	float dr = closestUtil(points + mid, n-mid);
	float d = minimum(dl, dr);
	
	point2d strip[n];
	int i, j = 0;
	for(i = 0; i < n; i++){
		if(abs(points[i].x - midpoint.x) < d){
			strip[j] = points[i];
			j++;
		}
	}
	return minimum(d, stripClosest(strip, j, d));
}

float closest(point2d points[], int n){
	printf("IN CLOSEST\n");
	qsort(points, n, sizeof(point2d), compareX);
	return closestUtil(points, n);
}

void closestpair2d(point2d *points, int n){
	printf("IN CLOSEST PAIR 2d\n");
	float d = closest(points, n);
	printf("Smallest dist = %f\n", d);
}

/*void closestpair3d(struct point3d *close3d, struct point3d *plane,int m)
{

	find out the closest pair of points among the points in "plane" and store them in the array close3d
}

void euclideanMST(struct point2d **mst,struct point2d *points,int n)
{
	find out the Euclidean MST and store the MST in 2d-array mst.
	   Each of the n-1 edges are store by storing it's two endpoints.
	
}*/

int main()
{
        point2d *points/*, close2d[2],**mst*/;
        //struct point3d *plane,close3d[2];
        int i, n/*, m*/;
        scanf("%d",&n);
        points = (point2d *)malloc(n*sizeof(point2d));
        for(i = 0; i < n; i++)
                scanf("%d%d",&(points[i].x),&(points[i].y));
        //scanf("%d",&m);
        //plane = (struct point3d *)mallloc(m*sizeof(struct point3d));
        //for(i=0;i<m;i++)
                //scanf("%d%d%d",&(plane[i].x),&(plane[i].y),&(plane[i].z));
        closestpair2d(points,n);
        //closestpair3d(close3d,plane,m);
        //mst = (struct point2d **)mallloc((n-1)*sizeof(struct point2d *));
        //for(i=0;i<n;i++)
                //mst[i]=(struct point2d *)mallloc(2*sizeof(struct point2d));
        //euclideanMST(mst,points,n);
        return 0;
}
