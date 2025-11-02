#include <stdio.h>

// Function declarations
void update(int g[3][3], int rows, int cols);
void query(int g[3][3], int rows, int cols);
void diag(int g[3][3], int rows, int cols);

int main() {
    int g[3][3] = {0};  
    int ch;  

    do {
        printf("\n--- IESCO Power Grid ---\n");
        printf("1. Update sector\n");
        printf("2. Query sector\n");
        printf("3. Run diagnostic\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &ch);

        if (ch == 1) {
            update(g, 3, 3);
        }
        else if (ch == 2) {
            query(g, 3, 3);
        }
        else if (ch == 3) {
            diag(g, 3, 3);
        }
        else if (ch == 4) {
            printf("Exiting program.\n");
        }
        else {
            printf("Invalid choice. Please enter 1-4.\n");
        }

    } while (ch != 4);

    return 0;
}

void update(int g[3][3], int rows, int cols) {
    int r, c, f, s;
    int mask;

    printf("Enter row (0-%d): ", rows - 1);
    scanf("%d", &r);
    printf("Enter col (0-%d): ", cols - 1);
    scanf("%d", &c);

    if (r < 0 || r >= rows) {
        printf("Invalid row.\n");
        return;
    }
    if (c < 0 || c >= cols) {
        printf("Invalid column.\n");
        return;
    }

    printf("Select flag to modify:\n");
    printf("0 = Power (ON/OFF)\n");
    printf("1 = Overload Warning\n");
    printf("2 = Maintenance Required\n");
    printf("Enter flag (0-2): ");
    scanf("%d", &f);

    
    if (f == 0) {
        mask = 1;  
    }
    else if (f == 1) {
        mask = 2;   
    }
    else if (f == 2) {
        mask = 4; 
    }
    else {
        printf("Invalid flag.\n");
        return;
    }

    printf("Enter 1 to SET or 0 to CLEAR this flag: ");
    scanf("%d", &s);

    if (s == 1) {
        g[r][c] = g[r][c] | mask;
        printf("Flag %d set at (%d,%d).\n", f, r, c);
    }
    else if (s == 0) {
        g[r][c] = g[r][c] & (~mask);
        printf("Flag %d cleared at (%d,%d).\n", f, r, c);
    }
    else {
        printf("Invalid input. Use 1 or 0.\n");
    }
}

void query(int g[3][3], int rows, int cols) {
    int r, c;
    int val;

    printf("Enter row (0-%d): ", rows - 1);
    scanf("%d", &r);
    printf("Enter col (0-%d): ", cols - 1);
    scanf("%d", &c);

    if (r < 0 || r >= rows || c < 0 || c >= cols) {
        printf("Invalid coordinates.\n");
        return;
    }

    val = g[r][c];

    printf("\nStatus for sector (%d,%d):\n", r, c);

    if ((val & 1) == 1) {
        printf("Power: ON\n");
    } else {
        printf("Power: OFF\n");
    }

    if ((val & 2) == 2) {
        printf("Overload Warning: YES\n");
    } else {
        printf("Overload Warning: NO\n");
    }

    if ((val & 4) == 4) {
        printf("Maintenance is Required: YES\n");
    } else {
        printf("Maintenance is Required: NO\n");
    }
}

void diag(int g[3][3], int rows, int cols) {
    int i, j;
    int overload = 0;
    int maint = 0;

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            if ((g[i][j] & 2) == 2) {
                overload++;
            }
            if ((g[i][j] & 4) == 4) {
                maint++;
            }
        }
    }

    printf("\n--- Diagnostics Report ---\n");
    printf("Overloaded sectors: %d\n", overload);
    printf("Sector needing maintenance: %d\n", maint);
}
