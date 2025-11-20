public class FineCalculator {
    private double finePerDay;

    // Constructors
    public FineCalculator() {
        this.finePerDay = 0.5; // Default value
    }

    public FineCalculator(double finePerDay) {
        this.finePerDay = (finePerDay > 0) ? finePerDay : 0.5;
    }

    // Public methods
    public double calculateFine(int daysOverdue) {
        if (daysOverdue > 0) {
            return daysOverdue * finePerDay;
        }
        return 0.0; // There is no penalty if there is no delay.
    }

    // Getter
    public double getFinePerDay() { return finePerDay; }
}