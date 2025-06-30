import java.util.ArrayList;
public class Organization{
     private String name;
     private Admin admin;
     private ArrayList<Entity> entityList;
     private ArrayList<Donator> donatorList;
     private ArrayList<Beneficiary> beneficiaryList;
     private RequestDonationList currentDonations;
    
     public Organization(String name,Admin admin)
     {
         this.name=name;
         this.admin=admin;
         this.entityList= new ArrayList<> ();
         this.donatorList=new ArrayList<>();
         this.beneficiaryList=new ArrayList<>();
         this.currentDonations=new RequestDonationList();
     }

     public Admin  getAdmin()
     {
          return admin;
     }
  
     public void addEntity(Entity e)
     throws Exception {
    for (Entity en : entityList) {
        if (en.getId() == e.getId()) throw new Exception("Το entity υπάρχει ήδη.");
    }
    entityList.add(e);
}
     
    public void removeEntity(Entity e, Admin caller) throws Exception {
    if (!caller.equals(admin)) throw new Exception("Μόνο ο Admin μπορεί να διαγράψει entity.");
    entityList.removeIf(en -> en.getId() == e.getId());
}

     public void insertDonator(Donator d)throws Exception {
    for (Donator dn : donatorList) {
        if (dn.getName().equals(d.getName()) && dn.getPhone().equals(d.getPhone())) throw new Exception("O Donator υπάρχει ήδη.");
    }
    donatorList.add(d);
}

     
     public void removeDonator(Donator d)
     {
          donatorList.remove(d);

     }

     public void insertBeneficiary(Beneficiary b)throws Exception {
    for (Beneficiary bn : beneficiaryList) {
        if (bn.getName().equals(b.getName()) && bn.getPhone().equals(b.getPhone())) throw new Exception("Το Beneficiary υπάρχει ήδη.");
    }
    beneficiaryList.add(b);
}

     

     public void removeBeneficiary(Beneficiary beneficiary)
     {
           beneficiaryList.remove(beneficiary);
     }

public void listEntities() {
    System.out.println("📦 Materials:");
    for (Entity e : entityList) {
        if (e instanceof Material) System.out.println(e);
    }

    System.out.println("🛠️ Services:");
    for (Entity e : entityList) {
        if (e instanceof Service) System.out.println(e);
    }
}
public void listBeneficiaries() {
    for (Beneficiary b : beneficiaryList) {
        System.out.println("👤 " + b.getName() + " | Παροχές:");
        for (RequestDonation rd : b.getReceivedList().getList()) {
            System.out.println("  " + rd.getEntity().getName() + ": " + rd.getQuantity());
        }
    }
}

public void listDonators() {
    for (Donator d : donatorList) {
        System.out.println("🙋 Donator: " + d.getName());
    }
}
public RequestDonationList getCurrentDonations() {
    return currentDonations;
}
public ArrayList<Entity> getEntityList() {
    return entityList;
}
}