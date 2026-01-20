import java.time.LocalDate;
import java.time.temporal.ChronoUnit;
import java.time.format.DateTimeFormatter;

public class FineCalculator {
	private final int FINE_PER_DAY = 5;
    private static final DateTimeFormatter FORMATTER = DateTimeFormatter.ofPattern("yyyy-MM-dd");

    // Public methods
    public double calculateFine(Transaction t) {
        if (!t.isActiveStatus()) {
        	return 0.0;
        }
        
        LocalDate today = LocalDate.now();
        LocalDate dueDate = LocalDate.parse(t.getDueDate(), FORMATTER);

        if (today.isAfter(dueDate)) {
            long daysOverdue = ChronoUnit.DAYS.between(dueDate, today);
            return (double) daysOverdue * FINE_PER_DAY;
        }
        return 0.0; // There is no penalty if the book is returned on time or earlier.
    }
}