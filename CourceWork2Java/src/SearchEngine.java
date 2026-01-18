import java.util.ArrayList;
import java.util.List;

public class SearchEngine {

    // Конструкторы
    public SearchEngine() {
        // System.out.println("SearchEngine: Constructor called.");
    }

    // Публичные методы
    public List<Book> searchByTitle(List<Book> books, String query) {
        List<Book> results = new ArrayList<>();
        if (query == null || query.isEmpty()) return results; // Пустой запрос

        //String lowerQuery = query.toLowerCase();
        for (Book book : books) {
			if (book.getTitle().toLowerCase().contains(query.toLowerCase())) { /*
													 * || book.getAuthor().toLowerCase().contains(lowerQuery)) {
													 */// Ищем по названию или автору
                results.add(book);
            }
        }
        //System.out.println("SearchEngine: Found " + results.size() + " book(s) for query '" + query + "'.");
        return results;
    }

    public List<Book> searchByAuthor(List<Book> books, String query) {
        List<Book> results = new ArrayList<>();
//        if (query == null || query.isEmpty()) return results;
//
//        String lowerQuery = query.toLowerCase();
        for (Book book : books) {
            if (book.getAuthor().toLowerCase().contains(query.toLowerCase())) /*||
                user.getEmail().toLowerCase().contains(lowerQuery)) */{ // Ищем по имени или email
                results.add(book);
            }
        }
        //System.out.println("SearchEngine: Found " + results.size() + " user(s) for query '" + query + "'.");
        return results;
    }
}