public class Service extends Entity{
       public Service(String name,String description,int id)
       {
           super(name,description,id);
       }
        
        public String getDetails()
        {
              return "The object is service";
        }
}