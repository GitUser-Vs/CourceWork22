import java.util.ArrayList;
import java.util.List;

public class SearchEngine {

    // Constructors
    public SearchEngine() {
        // System.out.println("SearchEngine: Constructor called.");
    }

    // Public methods
    public List<Book> searchByTitle(List<Book> books, String query) {
        List<Book> results = new ArrayList<>();
        if (query == null || query.isEmpty()) return results; // Empty request

        for (Book book : books) {
			if (book.getTitle().toLowerCase().contains(query.toLowerCase())) {
                results.add(book);
            }
        }
        return results;
    }

    public List<Book> searchByAuthor(List<Book> books, String query) {
        List<Book> results = new ArrayList<>();

        for (Book book : books) {
            if (book.getAuthor().toLowerCase().contains(query.toLowerCase())) {
                results.add(book);
            }
        }
        return results;
    }
}