import java.util.ArrayList;
import java.util.List; // Используем List для гибкости

public class SearchEngine {

    // Конструкторы
    public SearchEngine() {
        // System.out.println("SearchEngine: Constructor called.");
    }

    // Публичные методы
    public List<Book> searchBooksByTitle(List<Book> allBooks, String query) {
        List<Book> results = new ArrayList<>();
        if (query == null || query.isEmpty()) return results; // Пустой запрос

        String lowerQuery = query.toLowerCase();
        for (Book book : allBooks) {
            if (book.getTitle().toLowerCase().contains(lowerQuery) ||
                book.getAuthor().toLowerCase().contains(lowerQuery)) { // Ищем по названию или автору
                results.add(book);
            }
        }
        System.out.println("SearchEngine: Found " + results.size() + " book(s) for query '" + query + "'.");
        return results;
    }

    public List<User> searchUsersByName(List<User> allUsers, String query) {
        List<User> results = new ArrayList<>();
        if (query == null || query.isEmpty()) return results;

        String lowerQuery = query.toLowerCase();
        for (User user : allUsers) {
            if (user.getName().toLowerCase().contains(lowerQuery) ||
                user.getEmail().toLowerCase().contains(lowerQuery)) { // Ищем по имени или email
                results.add(user);
            }
        }
        System.out.println("SearchEngine: Found " + results.size() + " user(s) for query '" + query + "'.");
        return results;
    }
}