import java.time.LocalDate;
import java.time.temporal.ChronoUnit;
import java.time.format.DateTimeFormatter;

public class FineCalculator {
	private final int FINE_PER_DAY = 5;
    private static final DateTimeFormatter FORMATTER = DateTimeFormatter.ofPattern("yyyy-MM-dd");

    // Конструкторы
//    public FineCalculator() {
//        this.finePerDay = 0.5; // Значение по умолчанию
//  
//    }
//
//    public FineCalculator(double finePerDay) {
//        this.finePerDay = (finePerDay > 0) ? finePerDay : 0.5;
//
//    }

    // Публичные методы
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
        return 0.0; // Нет штрафа, если книга возвращена вовремя или раньше
    }

    // Геттер
//    public double getFinePerDay() { return finePerDay; }
}