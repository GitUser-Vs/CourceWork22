import java.io.Serializable;

public class Account implements Serializable {
    private static final long serialVersionUID = 1L;
    
    private String username;
    private String password;
    private Role role;
    private int associatedId;

    public Account(String user, String pass, Role r, int id) {
        this.username = user;
        this.password = pass;
        this.role = r;
        this.associatedId = id;
    }
    
    public Account() {}

    // Getters
    public String getUsername() { return username; }
    public String getPassword() { return password; }
    public Role getRole() { return role; }
    public int getAssociatedId() { return associatedId; }
}