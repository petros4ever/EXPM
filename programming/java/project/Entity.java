public abstract class Entity{
     private String name;
     private String description;
     private int id;

     public Entity(String name,String description,int id)
     {
          this.name=name;
          this.description=description;
          this.id=id;
     }
   
     public String getEntityInfo()
     {
          return "Name:"+ name +"Description: "+ description +"id: "+ id;
     }

      public abstract String getDetails();
 
     public String toString() 
    {
        return getEntityInfo() + " | " + getDetails();
    }
}