import java.io.Serializable;

public class User implements Serializable {
	private static final long serialVersionUID = 1L;
	
	private int userId;
	private String name;
    private String contact;
    
    // Constructors
    public User() {
    	//this(0, "Unknown User", "", 0);
    }

    public User(int id, String n, String c) {
        this.userId = id;
        this.name = n;
        this.contact = c;
    }
    
    // Public methods
    public void display() {
    	System.out.println("User ID: " + userId + " | Имя: " + name 
                + " | Контакт: " + contact);
    }

    // Getters
    public int getId() { return userId; }
    public String getName() { return name; }
}