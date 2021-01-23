#include "stdio.h"
#include "stdlib.h"
#include "string.h"

#define DIMENSIONS 2
#define NUM_OF_SIDES 3
#define NUM_OF_POINTS 4

enum point_symbols {
    A_SYM = 65,
    B_SYM,
    C_SYM,
    D_SYM
};

enum points {
	A = 0,
	B,
	C,
	D
};

/**
 * triangle_points - Contains values of points.
 * @z: pointer to results of cross product.
 * @x: array of x axis coordinates of points.
 * @y: array of y axis coordinates of points.
 * @tr_name: pointer to names of triangles.
 *
 * This structure saves parameters of point for comfortable using.  
 */
struct triangle_points
{
	int **z;
	int *x;
	int *y;
	char **tr_name;
};

/**
 * Sets the triangle name of the corresponding index.
 * @tr: 	pointer to points structure.
 * @name: 	string value of wanted name.
 * @num: 	index of name in structure.
 *
 * Changes the value of the corresponding name. max length is 3 symbols.
 */
void change_triangle_name(struct triangle_points *tr, char *name, int num) 
{
	for(int i = 0; i < NUM_OF_SIDES; i++) {
		tr->tr_name[num][i] = name[i];
	}
}

/**
 * Counts cross product of z component.
 * @tr:  pointer to points structure.
 * @num: index of point in structure.
 *
 * Counts cross product of the corresponding vectors.
 */
void count_cross_product_z(struct triangle_points *tr, char point, int num)
{
	 switch(point)
    {
        case A_SYM: 
           	tr->z[num][0] = (tr->x[C] - tr->x[B]) * (tr->y[A] - tr->y[B]) - (tr->y[C] - tr->y[B]) * (tr->x[A] - tr->x[B]);
			tr->z[num][1] = (tr->x[D] - tr->x[C]) * (tr->y[A] - tr->y[C]) - (tr->y[D] - tr->y[C]) * (tr->x[A] - tr->x[C]);
			tr->z[num][2] = (tr->x[B] - tr->x[D]) * (tr->y[A] - tr->y[D]) - (tr->y[B] - tr->y[D]) * (tr->x[A] - tr->x[D]);
			change_triangle_name(tr, "BCD", num);
            break;
        case B_SYM: 
            tr->z[num][0] = (tr->x[C] - tr->x[A]) * (tr->y[B] - tr->y[A]) - (tr->y[C] - tr->y[A]) * (tr->x[B] - tr->x[A]);
			tr->z[num][1] = (tr->x[D] - tr->x[C]) * (tr->y[B] - tr->y[C]) - (tr->y[D] - tr->y[C]) * (tr->x[B] - tr->x[C]);
			tr->z[num][2] = (tr->x[A] - tr->x[D]) * (tr->y[B] - tr->y[D]) - (tr->y[A] - tr->y[D]) * (tr->x[B] - tr->x[D]);
			change_triangle_name(tr, "ACD", num);
            break;
        case C_SYM: 
            tr->z[num][0] = (tr->x[B] - tr->x[A]) * (tr->y[C] - tr->y[A]) - (tr->y[B] - tr->y[A]) * (tr->x[C] - tr->x[A]);
			tr->z[num][1] = (tr->x[D] - tr->x[B]) * (tr->y[C] - tr->y[B]) - (tr->y[D] - tr->y[B]) * (tr->x[C] - tr->x[B]);
			tr->z[num][2] = (tr->x[A] - tr->x[D]) * (tr->y[C] - tr->y[D]) - (tr->y[A] - tr->y[D]) * (tr->x[C] - tr->x[D]);
			change_triangle_name(tr, "ABD", num);
            break;
        case D_SYM:
            tr->z[num][0] = (tr->x[B] - tr->x[A]) * (tr->y[D] - tr->y[A]) - (tr->y[B] - tr->y[A]) * (tr->x[D] - tr->x[A]);
			tr->z[num][1] = (tr->x[C] - tr->x[B]) * (tr->y[D] - tr->y[B]) - (tr->y[C] - tr->y[B]) * (tr->x[D] - tr->x[B]);
			tr->z[num][2] = (tr->x[A] - tr->x[C]) * (tr->y[D] - tr->y[C]) - (tr->y[A] - tr->y[C]) * (tr->x[D] - tr->x[C]);
			change_triangle_name(tr, "ABC", num);
            break;    
      }
	
}

/**
 * Checks if point inside of the triangle.
 * @tr:  pointer to points structure.
 * @num: index of point in structure.
 * @return: 1 if the point inside and 0 if the point outside.
 *
 * Checks if point inside or outside of the triangle. If the point on edge it means it is in the triangle.
 */
int point_within_triangle(struct triangle_points *tr, int num) 
{
	if (( tr->z[num][0] >= 0 && tr->z[num][1] >= 0 && tr->z[num][2] >= 0) || ( tr->z[num][0] <= 0 && tr->z[num][1] <= 0 && tr->z[num][2] <= 0))
		return 1;
	 else
	 	return 0;
}

/**
 * Puts values from file into structure of points.
 * @tr:  pointer to points structure.
 * @name: name of the file.
 *
 * If the file does not exist, the program finishes.
 */
void file_to_coordinates(struct triangle_points *tr, char *name)
{
	unsigned char *buffer;
	FILE *fp;
	int flen;

	if ((fp= fopen(name, "r")) == NULL) {
       	fprintf(stderr, "An error occurred while opening file %s\n", name);
       	exit(0);
    }

	fseek(fp, 0, SEEK_END);
	flen = ftell(fp);
	rewind(fp);

	buffer = (unsigned char *)malloc(flen * sizeof(*buffer));

	fread(buffer, flen, 1, fp);
	fclose(fp);

	char *token = strtok(buffer, " ");

   	for(int i = 0; i < NUM_OF_POINTS*2; i++) {
   		
   		if(i%2 == 0)
   			tr->x[i/2] = atof(token);
   		else 
   			tr->y[i/2] = atof(token);

   		token = strtok(NULL, " ");
   	}
   	free(buffer);
}

/**
 * Prints the status of a points.
 * @tr:  pointer to points structure.
 *
 * Run only after all calculations.
 */
void print_message(struct triangle_points *tr)
{
	for(int i = 0; i < NUM_OF_POINTS; i++) {
		count_cross_product_z(tr, A_SYM + i, i);
		if(point_within_triangle(tr, i)) 
			printf("point %c inside the triangle %s\n", A_SYM + i, tr->tr_name[i]);
		else
			printf("point %c outside the triangle %s\n", A_SYM + i, tr->tr_name[i]);
	}
}

/**
 * Inits structure of points.
 * @tr:  pointer to points structure.
 *
 * Allocates memory for structure variables.
 */
void init_points(struct triangle_points *tr) 
{
	tr->x = calloc(NUM_OF_POINTS, sizeof(int));
	tr->y = calloc(NUM_OF_POINTS, sizeof(int));
	tr->z = calloc(NUM_OF_POINTS, sizeof(int *));
	tr->tr_name = calloc(NUM_OF_POINTS, sizeof(char*));
	for(int i = 0; i < NUM_OF_POINTS; i++) {
		tr->z[i] = calloc(NUM_OF_SIDES, sizeof(int));
		tr->tr_name[i] = calloc(NUM_OF_SIDES, sizeof(char));
	}
}

int main(int argc, char *argv[])
{
	struct triangle_points tr_points;
	init_points(&tr_points);								/** initialization of the structure */

	if(argc == 9) {											/** coordinates of points are given in command-line arguments */
		for (int i = 1; i <= NUM_OF_POINTS; i++) {
			tr_points.x[i-1] = atof(argv[i*2 - 1]);
			tr_points.y[i-1] = atof(argv[i*2]);
		}
	} else if (argc == 2) {									/** coordinates of points are given in the file */
		file_to_coordinates(&tr_points, argv[1]);
	} else {												/** user types in coordinates during programs workflow */
		for(int i = 0; i < NUM_OF_POINTS; i++) {
    		printf("enter point %c: ", A_SYM + i);
    		scanf("%d %d", &tr_points.x[i], &tr_points.y[i]);
    		printf("%c[%d;%d]\n", A_SYM + i, tr_points.x[i], tr_points.y[i]);
  		}
	}
	print_message(&tr_points);

	return 0;
}	