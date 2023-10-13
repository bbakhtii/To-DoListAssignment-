#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


struct Task {
    string description;
    string dueDate;
    bool completed;
};

void presentTable (){
    cout<<"Table: \n";
    cout<<"1.Add a new task\n";
    cout<<"2.Mark as a completed work\n";
    cout<<"3.View all the tasks from the list\n";
    cout<<"4.Remove the tasks\n";
    cout<<"5.Exit\n";
    cout<<"Choose one option from the listed above:";
}
void  addTask(vector <Task>& tasks){

    Task newTask;
    cout<<"Enter the task description: ";
    cin.ignore();
    getline(cin,newTask.description);
    cout<<"Enter the due date: ";
    cin>>newTask.dueDate;
    newTask.completed = false;
    tasks.push_back(newTask);
    cout<<"Task added successfully!\n";
};

void markTaskCompleted(vector<Task>& tasks){
    cout<<"Enter the index of the task to mark  as completed: ";
    int index;
    cin>>index;
    if (index >=0 && index < tasks.size()){
        tasks[index].completed=true;
        cout<<"Task marked as completed!\n";
    }
    else{
        cout<<"Invalid index\n";
    }
}

bool compareTasks(const Task& a, const Task& b){
    return a.dueDate < b.dueDate;
}
void viewTaks( const vector<Task>& tasks){
    cout<<"List of tasks: \n";
    cout<<"Index\tDescription\tDueDate\tStatus\n";

    int index=0;
    for (const Task& task : tasks){
        cout<<index<<"\t"<<task.description<<"\t"<<task.dueDate<<"\t"<<(task.completed ? "Completed": "Incomplete")<< "\n";
        index++;
    }
    cout<<"\n";

}

void removeTasks(vector <Task>& tasks){
    cout<<"Enter the index of the task to remove: ";

    int index;
    cin>>index;
    if( index>=0 && index<tasks.size()){

        tasks.erase(tasks.begin()+index);
        cout<<"Task removed successefully\n";
    }
    else{
        cout<<"Invalid index\n";
    }

}
int main(){
    vector <Task> tasks;
    int choice;
    do{
        presentTable();
        cin>>choice;

        switch(choice){
        
    case 1:
        addTask(tasks);
        break;
    case 2:
        markTaskCompleted(tasks);
        break;
    case 3:
        sort(tasks.begin(),tasks.end(),compareTasks);
        break;
    case 4:
        removeTasks(tasks);
        break;
    case 5:
        cout<<"GoodBye!\n";
        break;
    default:
        cout<<"Invalid choice\n";
        break;
     }
        cout<<"\n";

    }while(choice!=5);
    return 0;
}