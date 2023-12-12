#include <iostream>
#include <conio.h>
#include <vector>
#include <string>
using namespace std;
int s = 0;
void mainmenu();
void adminmenu();
void customermenu();

class Admin {
private:
    string train_plan[3];
    float train_cost[3];
public:
    void insert_plan() {
        for (int i = 0; i < 3; i++) {
            cin.ignore();
            cout << "Enter Training Plan\n";
            getline(cin, train_plan[i]);
            cout << "Enter Training Cost\n";
            cin >> train_cost[i];
        }
    }
    void view_training_plan() {
        cout << "Training Plan\t\t\tTraining Cost\n";
        for (int i = 0; i < 3; i++) {
            cout << i + 1 << train_plan[i] << "\t\t" << train_cost[i] << endl;
        }
    }
    void update_plan() {
        int plan_number;
        // Display current training plans
        cout << "Current Training Plans:\n";
        view_training_plan();
        cout << "Enter the number of the plan you want to update: ";
        cin >> plan_number;
        if (plan_number >= 1 && plan_number <= 3) {
            cin.ignore();
            cout << "Enter updated Training Plan: ";
            getline(cin, train_plan[plan_number - 1]);
            cout << "Enter updated Training Cost: ";
            cin >> train_cost[plan_number - 1];
            cout << "Training plan updated successfully.\n";
            // Display updated training plans
            cout << "Updated Training Plans:\n";
            view_training_plan();
        } else {
            cout << "Invalid plan number.\n";
        }
    }
};
Admin obj_admin;
class Customer : public Admin {
public:
    string customer_name;
    int t_plan;
    string cu_plan;
    string weight;
    char tution;
    int tution_hr;
    float beginner_fees = 20;
    float intermediate_fees = 30;
    float elite_fees = 40;
    float tution_fees = 23000.00;
    float total_cost = 0;
    float private_t;
    string cur_weight;
    char competition;
    int race;
    float comp_fees = 22.00;
    int comp = 0;
    float private_tution(char c) {
        if (c == 'y') {
            cout << "Enter private tution hours \n";
            cin >> tution_hr;
            if (tution_hr < 5) {
                total_cost += (tution_fees * tution_hr);
                return total_cost;
            } else {
                cout << "You exceed the limited private hours\n";
                private_tution(c);
            }
        } else {
            return total_cost;
        }
    }
    int weight_categories() {
        int race = 1;
        int current_weight;
        cout << "\n=========Competition weight Categories========\n\n";
        cout << "Categories\t\t\tWeight Limit\n";
        cout << "1. Heavy Weight\t\t\tover 100\n";
        cout << "2. Light Heavy Weight\t\t100\n";
        cout << "3. Middle Weight\t\t\t90\n";
        cout << "4. Light_MiddleWeight\t\t81\n";
        cout << "5. Light Weight\t\t\t73\n";
        cout << "6. Flyweight\t\t\t66\n";
        cout << "Enter your current weight\n";
        cin >> current_weight;
        if (current_weight > 100) {
            cout << "You can join Heavy Weight Competition \n";
            cur_weight = "Heavy Weight";
        } else if (current_weight == 100) {
            cout << "You can join Light Heavyweight Competition \n";
            cur_weight = "Light Weight";
        } else if ((current_weight < 100) && (current_weight >= 90)) {
            cout << "You can join Middleweight Competition \n";
            cur_weight = "Middle Weight";
        } else if (current_weight < 90 && current_weight >= 81) {
            cout << "You can join Light Middleweight Competition \n";
            cur_weight = "Light Middle Weight";
        } else if (current_weight < 81 && current_weight >= 73) {
            cout << "You can join Lightweight Competition \n";
            cur_weight = "Light Weight";
        } else if (current_weight < 73 && current_weight >= 66) {
            cout << "You can join Flyweight Competition \n";
            cur_weight = "Fly Weight";
        } else {
            cout << "You can't compete\n";
            race = 0;
        }
        return race;
    }
    void getdata() {
        cin.ignore();
        cout << "Enter customer name\n";
        getline(cin, customer_name);
        obj_admin.view_training_plan();
        cin >> t_plan;
        if (t_plan == 1) {
            cu_plan = "beginner";
            total_cost += beginner_fees;
        } else if (t_plan == 2) {
            cu_plan = "intermediate";
            total_cost += intermediate_fees;
        } else if (t_plan == 3) {
            cu_plan = "Elite";
            total_cost += elite_fees;
        }
        if ((t_plan == 2) || (t_plan == 3)) {
            race = weight_categories();
            if (race == 1) {
                cout << "You can join competition\n";
                cout << "Enter number of competition\n";
                cin >> comp;
                total_cost += (comp_fees * comp);
            }
        } else {
            cout << "You can't compete, you are a beginner \n";
        }
        cout << "Private tution (y/n)\n";
        cin >> tution;
        private_t = private_tution(tution);
    }
    void showdata() {
		cout<<customer_name<<'\t'<<'\t'<<total_cost<<'\t'<<'\t'<<'\t'<<cu_plan<<'\t'<<'\t'<<cur_weight<<endl;
    }
};
vector<Customer> obj_customer(100); // Assuming a maximum of 100 customers
// Merge Sort implementation for sorting customer information by name
void merge(vector<Customer>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    vector<Customer> L(n1);
    vector<Customer> R(n2);
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    int i = 0;
    int j = 0;
    int k = left;
    while (i < n1 && j < n2) {
        if (L[i].customer_name <= R[j].customer_name) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}
void mergeSort(vector<Customer>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}
// Modify the "View information" section to use the sorted customer information
void viewSortedInformation() {
    if (s > 0) {
        // Copy the array to avoid modifying the original order
        vector<Customer> sortedCustomers(obj_customer.begin(), obj_customer.begin() + s);
        // Sort the array using mergeSort
        mergeSort(sortedCustomers, 0, s - 1);
        for (int i = 0; i < s; i++) {
            sortedCustomers[i].showdata();
        }
    } else {
        cout << "No customer information available.\n";
    }
}
// Modify the customermenu() function to call viewSortedInformation()
void customermenu() {
    int customer_task;
    char ch;
    cout << "1. Register\n2. View information\n";
    cin >> customer_task;
    if (customer_task == 1) {
        do {
            obj_customer[s].getdata();
            cout << "Do you want to continue more registrations (y/n)\n";
            cin >> ch;
            s++;
        } while (ch == 'y');
        customermenu();
    } else if (customer_task == 2) {
        cout << "Customer Name"<<'\t'<<'\t'<<"Total Cost"<<'\t'<<'\t'<<"Training Plan"<<'\t'<<'\t'<<"Current Weight"<<endl;
        viewSortedInformation();
    }
}
void mainmenu() {
    int user;
    cout << "1. Admin\n2. Customer\n3. Guest\n";
    cin >> user;
    if (user == 1) {
        adminmenu();
        getch();
    } else if (user == 2) {
        customermenu();
    }
}
void adminmenu() {
    int admin_task;
    cout << "1. Insert plan\n2. Update\n3. View Training Plan\n";
    cin >> admin_task;
    if (admin_task == 1) {
        obj_admin.insert_plan();
        getch();
        mainmenu();
    } else if (admin_task == 2) {
        obj_admin.update_plan();
        getch();
        mainmenu();
    } else if (admin_task == 3) {
        obj_admin.view_training_plan();
        getch();
        mainmenu();
    }
}
int main() {
    mainmenu();
    return 0;
}