public class Admin extends User{
     public Admin(String name,String phone)
     {
         super(name,phone);
     }
      
     public boolean isadmin()
     {
         return true;
     }
}