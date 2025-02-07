#include <iostream>
#include <vector>
#include <cmath>
#include <limits>
#include <iomanip>

using namespace std;

struct LoanTerms {
    double amount;
    double interestRate;
    int tenureYears;
    string repaymentFrequency;
};

class LoanCalculator {
private:
    const double BASE_RATE_SALARIED = 10.5;
    const double BASE_RATE_SELF_EMPLOYED = 12.0;
    const double MIN_LOAN_AMOUNT = 50000;
    
    double getMaxLoanAmount(double annualIncome, int employmentStatus) {
        return (employmentStatus == 1) ? annualIncome * 5 : annualIncome * 3;
    }

public:
    void calculateEMI(const LoanTerms &terms) {
        double monthlyRate = terms.interestRate / 12 / 100;
        int months = terms.tenureYears * 12;
        double emi = (terms.amount * monthlyRate * pow(1 + monthlyRate, months)) 
                    / (pow(1 + monthlyRate, months) - 1);

        cout << "\nRepayment Schedule:\n";
        cout << "EMI: ₹" << fixed << setprecision(2) << emi << " per month\n";
        
        if(terms.repaymentFrequency == "Quarterly") {
            cout << "Quarterly Payment: ₹" << emi * 3 << endl;
        }
        else if(terms.repaymentFrequency == "Annual") {
            cout << "Annual Payment: ₹" << emi * 12 << endl;
        }
    }

    LoanTerms getLoanTerms(double annualIncome, int employmentStatus) {
        LoanTerms terms;
        
       
        terms.interestRate = (employmentStatus == 1) ? BASE_RATE_SALARIED 
                                                   : BASE_RATE_SELF_EMPLOYED;

        double maxAmount = getMaxLoanAmount(annualIncome, employmentStatus);
        do {
            cout << "\nEnter desired loan amount (₹" 
                 << fixed << setprecision(0) << MIN_LOAN_AMOUNT 
                 << " - ₹" << fixed << setprecision(0) << maxAmount 
                 << "): ";
            cin >> terms.amount;
        } while(terms.amount < MIN_LOAN_AMOUNT || terms.amount > maxAmount);

        do {
            cout << "Enter loan tenure (1-20 years): ";
            cin >> terms.tenureYears;
        } while(terms.tenureYears < 1 || terms.tenureYears > 20);

        // repayment frequency 
        int freqChoice;
        do {
            cout << "Repayment Frequency:\n1. Monthly\n2. Quarterly\n3. Annual\n";
            cout << "Choose (1-3): ";
            cin >> freqChoice;
        } while(freqChoice < 1 || freqChoice > 3);

        terms.repaymentFrequency = (freqChoice == 1) ? "Monthly" : 
                                  (freqChoice == 2) ? "Quarterly" : "Annual";

        return terms;
    }
};

int main() {
    LoanCalculator calculator;
    vector<string> rejectionReasons;
    int employmentStatus;
    double annualIncome;
    int creditScore;

    cout << "🏦 Smart Loan Advisor (₹) 🏦\n";
    cout << "============================\n";

    // Get employment status
    do {
        cout << "\nEmployment Status:\n1. Salaried\n2. Self-Employed\n3. Unemployed\n";
        cout << "Choose (1-3): ";
        cin >> employmentStatus;
    } while(employmentStatus < 1 || employmentStatus > 3);

    if(employmentStatus == 3) {
        rejectionReasons.push_back("Unemployment status");
        goto conclusion;
    }

    // annual salary
    do {
        cout << "Enter annual income (₹): ";
        cin >> annualIncome;
    } while(annualIncome <= 0);

    // credit score
    do {
        cout << "Enter credit score (300-900): ";
        cin >> creditScore;
    } while(creditScore < 300 || creditScore > 900);

    if((employmentStatus == 1 && annualIncome < 300000) || 
       (employmentStatus == 2 && annualIncome < 500000)) {
        rejectionReasons.push_back("Insufficient annual income");
    }

    if((employmentStatus == 1 && creditScore < 700) || 
       (employmentStatus == 2 && creditScore < 750)) {
        rejectionReasons.push_back("Inadequate credit score");
    }

conclusion:
    cout << "\n=== Loan Assessment Result ===\n";
    if(rejectionReasons.empty()) {
        cout << "✅ Approved!\n";
        LoanTerms terms = calculator.getLoanTerms(annualIncome, employmentStatus);
        cout << "\nLoan Offer Details:\n";
        cout << "Amount: ₹" << fixed << setprecision(2) << terms.amount << endl;
        cout << "Interest Rate: " << terms.interestRate << "% p.a.\n";
        cout << "Tenure: " << terms.tenureYears << " years\n";
        cout << "Repayment: " << terms.repaymentFrequency << endl;
        
        calculator.calculateEMI(terms);
    }
    else {
        cout << "❌ Declined. Reasons:\n";
        for(const string& reason : rejectionReasons) {
            cout << "- " << reason << endl;
        }
    }

    // Transaction limit 
    cout << "\nℹ️ Transaction Limits:\n";
    cout << "- Minimum Loan: ₹50,000\n";
    cout << "- Maximum Loan: " 
         << (employmentStatus == 1 ? "5x annual income" : "3x annual income") 
         << endl;

    return 0;
}