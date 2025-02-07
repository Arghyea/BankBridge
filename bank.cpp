#include <iostream>
#include <iomanip>
#include <vector>
#include <limits>

using namespace std;

class LoanCalculator {
private:
    const double BASE_RATE = 9.5;
    const double MANUFACTURING_RATE = 7.0;
    const double MIN_LOAN = 50000;
    const double MAX_GENERAL_LOAN = 5000000;
    const double MANUFACTURING_MIN_INVESTMENT = 10000000;

public:
    void calculateEMI(double amount, double rate, int years) {
        double monthlyRate = rate / 12 / 100;
        int months = years * 12;
        double emi = (amount * monthlyRate * pow(1 + monthlyRate, months)) 
                    / (pow(1 + monthlyRate, months) - 1);

        cout << "EMI: ₹" << fixed << setprecision(2) << emi << "/month\n";
    }

    void displayLoanTerms(bool isManufacturing, double investment) {
        cout << "\n=== SPECIAL PROVISIONS ===";
        if(isManufacturing && investment >= MANUFACTURING_MIN_INVESTMENT) {
            cout << "\n✅ Manufacturing Business Benefits:\n"
                 << "- Eligible for 15% capital subsidy (CLCSS Scheme) :cite[6]:cite[10]\n"
                 << "- Priority land allocation through Make in India initiative\n"
                 << "- Interest rate capped at " << MANUFACTURING_RATE << "%\n"
                 << "- GST reimbursement for first 3 years\n";
        }
    }

    void getLoanDetails(double annualIncome, int empStatus, bool isNewBusiness) {
        double maxLoan = (empStatus == 1) ? annualIncome * 3 : annualIncome * 2;
        maxLoan = min(maxLoan, MAX_GENERAL_LOAN);

        cout << "\nLoan Amount Ranges:\n";
        cout << "- General Public: ₹" << fixed << setprecision(2) << MIN_LOAN 
             << " - ₹" << maxLoan << endl;
        
        if(isNewBusiness) {
            cout << "- New Businesses: ₹" << MIN_LOAN << " - ₹1,00,00,000\n";
            cout << "- Manufacturing Startups: ₹10,00,000 - ₹5,00,00,000 "
                 << "(with ₹1cr+ investment)\n";
        }
    }
};

int main() {
    LoanCalculator calculator;
    vector<string> rejectionReasons;
    int empStatus;
    double annualIncome, businessInvestment = 0;
    bool isNewBusiness = false, isManufacturing = false;

    cout << "🏭 Smart Loan Advisor 2025 (₹) 🏭\n";
    cout << "=================================\n";

    do {
        cout << "\nEmployment Status:\n1. Salaried\n2. Self-Employed\n3. Unemployed\n";
        cout << "Choose (1-3): ";
        cin >> empStatus;
    } while(empStatus < 1 || empStatus > 3);

    cout << "Is this for a new business? (1-Yes/0-No): ";
    cin >> isNewBusiness;

    if(isNewBusiness) {
        cout << "Business Type:\n1. Manufacturing\n2. Other\nChoice: ";
        int bizType;
        cin >> bizType;
        isManufacturing = (bizType == 1);

        if(isManufacturing) {
            cout << "Enter planned investment (₹): ";
            cin >> businessInvestment;
        }
    }

    double minIncome = (empStatus == 1) ? 180000 : 240000;
    do {
        cout << "Enter annual income (₹): ";
        cin >> annualIncome;
    } while(annualIncome <= 0 && !isNewBusiness);

    if(isManufacturing && businessInvestment >= 10000000) {
        cout << "\n🌟 Special Manufacturing Package Activated 🌟\n";
        minIncome = 0; // Waive income requirements
    }

    if(annualIncome < minIncome && !isManufacturing) {
        rejectionReasons.push_back("Annual income below ₹" + to_string(minIncome));
    }

    calculator.getLoanDetails(annualIncome, empStatus, isNewBusiness);

    cout << "\n=== GOVERNMENT SCHEMES ===";
    if(isManufacturing) {
        cout << "\n- Credit-Linked Capital Subsidy (15% on ₹1cr+ investment)"
            << "\n- Make in India Interest Subsidy (2% rebate)"
            << "\n- Industrial Park Allocation Priority";
    }
    if(annualIncome < 300000) {
        cout << "\n- Eligible for Special Government Loan (₹50,000 at 1% interest)";
    }
    
    if(rejectionReasons.empty()) {
        double amount, rate = BASE_RATE;
        int tenure;
        
        if(isManufacturing && businessInvestment >= 10000000) {
            rate = MANUFACTURING_RATE;
            cout << "\n\n=== MANUFACTURING LOAN TERMS ===";
            cout << "\nMin. Investment: ₹1,00,00,000"
                 << "\nInterest Rate: " << rate << "%"
                 << "\nLand Acquisition: Government-assisted :cite[8]";
        }

        cout << "\n\nEnter desired amount (₹): ";
        cin >> amount;
        cout << "Enter tenure (years): ";
        cin >> tenure;

        calculator.displayLoanTerms(isManufacturing, businessInvestment);
        calculator.calculateEMI(amount, rate, tenure);
    }
    else {
        cout << "\n❌ Application Rejected. Reasons:\n";
        for(const auto& reason : rejectionReasons) {
            cout << "- " << reason << endl;
        }
    }

    return 0;
}
