
#include <iostream>

using namespace std;



int main() {

    float score1, score2, score3, average;

    cout << "Enter the score for the Exam 1:";

    cin >> score1;



    cout << "Enter the score for the Exam 2:";

    cin >> score2;



    cout << "Enter the score for the Exam 3:";

    cin >> score3;



    average = (score1 + score2 + score3) / 3;



    cout << "Average score:" << average << endl;



    if (average >= 70){

        cout << "Result: Passed" << endl;

    } else{

        cout << "Result: Failed" << endl;

    }






    return 0;

}