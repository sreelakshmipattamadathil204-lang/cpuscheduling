#include <stdio.h>
#include <string.h>

struct Process {
    char id[10];
    int at, bt, wt, tat, ft;
    int completed;
};

int main() {
    int n;
    scanf("%d", &n);
    struct Process p[n];

    for (int i = 0; i < n; i++) {
        scanf("%s %d %d", p[i].id, &p[i].at, &p[i].bt);
        p[i].completed = 0;
    }

    int current_time = 0, completed_count = 0;
    float total_wt = 0, total_tat = 0;

    while (completed_count < n) {
        int idx = -1;
        int min_bt = 1e9;

        // Find process with shortest BT among those that have arrived
        for (int i = 0; i < n; i++) {
            if (p[i].at <= current_time && !p[i].completed) {
                if (p[i].bt < min_bt) {
                    min_bt = p[i].bt;
                    idx = i;
                }
                // If burst times are equal, process with earlier arrival time gets priority
                if (p[i].bt == min_bt) {
                    if (idx != -1 && p[i].at < p[idx].at) {
                        idx = i;
                    }
                }
            }
        }

        if (idx != -1) {
            p[idx].ft = current_time + p[idx].bt;
            p[idx].tat = p[idx].ft - p[idx].at;
            p[idx].wt = p[idx].tat - p[idx].bt;
            
            total_wt += p[idx].wt;
            total_tat += p[idx].tat;
            p[idx].completed = 1;
            completed_count++;
            current_time = p[idx].ft;
        } else {
            // If no process has arrived, advance time
            current_time++;
        }
    }

    printf("Waiting Time:\n");
    for (int i = 0; i < n; i++) printf("%s %d\n", p[i].id, p[i].wt);

    printf("Turnaround Time:\n");
    for (int i = 0; i < n; i++) printf("%s %d\n", p[i].id, p[i].tat);

    printf("Average Waiting Time: %.2f\n", total_wt / n);
    printf("Average Turnaround Time: %.2f\n", total_tat / n);

    return 0;
}
