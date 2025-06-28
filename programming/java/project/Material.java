public class Material extends Entity{
     private final double level1;
     private final double level2;
     private final double level3;
    
     public Material(String name,String description,int id,double level1,double level2,double level3)
     {
         super(name,description,id);
         this.level1=level1;
         this.level2=level2;
         this.level3=level3;
     }
     
     public String getDetails()
     {
                  return "Material | Level1 (1 άτομο): " + level1 +
           ", Level2 (2-4 άτομα): " + level2 +
           ", Level3 (5+ άτομα): " + level3; 
     }
}