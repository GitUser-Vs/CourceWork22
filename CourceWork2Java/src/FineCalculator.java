import java.time.LocalDate;
import java.time.temporal.ChronoUnit;

public class FineCalculator {
    private double finePerDay;

    // Конструкторы
    public FineCalculator() {
        this.finePerDay = 0.5; // Значение по умолчанию
  
    }

    public FineCalculator(double finePerDay) {
        this.finePerDay = (finePerDay > 0) ? finePerDay : 0.5;

    }

    // Публичные методы
    public double calculateFine(LocalDate dueDate, LocalDate returnDate) {
        if (returnDate != null && returnDate.isAfter(dueDate)) {
            long daysOverdue = ChronoUnit.DAYS.between(dueDate, returnDate);
            return daysOverdue * finePerDay;
        }
        return 0.0; // Нет штрафа, если книга возвращена вовремя или раньше
    }

    // Геттер
    public double getFinePerDay() { return finePerDay; }
}