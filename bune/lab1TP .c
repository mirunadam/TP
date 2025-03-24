#include <stdio.h>

struct shapes2D{
    int flag_type;
    union data
    {
        struct circle{  
            int radius; 
            int x;
            int y;
        }c;
        struct rectangle{
            int x1, x2, y1, y2;
        }r;
        struct triangle{
            int x1, x2, x3, y1, y2, y3;
        }t;
    }u;

}shapeList[100];

void menu()
{
    printf("Menu:\n");
    printf("0. Exit\n");
    printf("1. Circle\n");
    printf("2. Rectangle\n");
    printf("3. Triangle\n");
}

int insert_shape(int opt){
    switch (opt)
    {
    case 0 :
        printf("...Exit program...");
        break;
    case 1 :
        printf("Input the circle coordinates:\n");
        break;
    case 2 :
        printf("Input the rectangle coordinates:\n");
        break;
    case 3 :
        printf("Input the triangle coordinates:\n");
        break;
    default:
        printf("Not an option!\n");
        break;
    }
    return opt;

}
int show_shapes(int opt, int k){
    switch(opt){
        case 1:
            printf("Shape %d is a circle\n", k);
            printf("The radius is: %d, and the center coordinates: %d, %d\n", shapeList[k].u.c.radius, shapeList[k].u.c.x, shapeList[k].u.c.y);
            break;
        case 2:
            printf("Shape %d is a rectangle\n", k);
            printf("The coordinates of the first point: %d, %d\n", shapeList[k].u.r.x1, shapeList[k].u.r.y1);
            printf("The coordinates of the second point: %d, %d\n", shapeList[k].u.r.x2, shapeList[k].u.r.y2);
            break;
        case 3:
            printf("Shape %d is a triangle\n", k);
            printf("The coordinates of the first point: %d, %d\n", shapeList[k].u.t.x1, shapeList[k].u.t.y1);
            printf("The coordinates of the second point: %d, %d\n", shapeList[k].u.t.x2, shapeList[k].u.t.y2);
            printf("The coordinates of the third point: %d, %d\n", shapeList[k].u.t.x3, shapeList[k].u.t.y3);
    }
    return 0;
}

int collect_coordinates(int opt){
    int k=0;
    switch(opt){
            case 0:
                printf("...Exit program...");
                break;
            case 1:
                shapeList[k++].flag_type=1;
                printf("Radius, x, y:\n");
                scanf("%d %d %d", &shapeList[k].u.c.radius, &shapeList[k].u.c.x, &shapeList[k].u.c.y);
                show_shapes(1, k);
                break;
            case 2:
                shapeList[k++].flag_type=2;
                printf("First point:\n");
                scanf("%d, %d", &shapeList[k].u.r.x1, &shapeList[k].u.r.y1);
                printf("Second point:\n");
                scanf("%d, %d", &shapeList[k].u.r.x2, &shapeList[k].u.r.y2);
                show_shapes(2, k);
                break;
            case 3:
                shapeList[k++].flag_type=3;
                printf("First point:\n");
                scanf("%d, %d", &shapeList[k].u.t.x1, &shapeList[k].u.t.y1);
                printf("Second point:\n");
                scanf("%d, %d", &shapeList[k].u.t.x2, &shapeList[k].u.t.y2);
                printf("Third point:\n");
                scanf("%d, %d", &shapeList[k].u.t.x3, &shapeList[k].u.t.y3);
                show_shapes(3, k);
                break;      
        }  
    return 0;
}

int main(){
    int posibilities=4; // the nr of posible options
    int opt;
    menu();
    while(posibilities != 0){
        printf("Make a choice:");
        scanf("%d", &opt);
        insert_shape(opt);
        collect_coordinates(opt);
        posibilities--;
    }
    return 0;
}