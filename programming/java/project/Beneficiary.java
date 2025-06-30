import java.util.ArrayList;
public class Beneficiary extends User{
     private int nopersons=1;
     private RequestDonationList receivedList;
     private Requests requestsList;
     private ArrayList<Entity> entityList;

     
     public Beneficiary(String name, String phone, int nopersons, Organization org) 
    {
        super(name, phone);
        this.nopersons = nopersons;
        this.receivedList = new RequestDonationList();
        this.entityList= new ArrayList<> ();
        this.requestsList = new Requests(this,org.getCurrentDonations());
    }
    
     public void addRequest(RequestDonation rd, ArrayList<Entity> entityList) throws Exception {
    requestsList.add(rd, entityList);
}

   public void removeRequest(Entity e) {
    requestsList.remove(e);
}

    public void addToReceivedList(RequestDonation rd, ArrayList<Entity> entityList) throws Exception {
    receivedList.add(rd, entityList);
}

   
    public double getEntitledQuantity(Entity e) {
    if (e instanceof Material) {
        Material m = (Material) e;
        if (nopersons == 1) return m.getLevel1();
        else if (nopersons <= 4) return m.getLevel2();
        else return m.getLevel3();
    }
    return Double.MAX_VALUE; }
   
  public void commitRequests(ArrayList<Entity> entityList, RequestDonationList currentDonations) throws Exception{
    for (RequestDonation rd : requestsList.getList()) {
        double entitled = getEntitledQuantity(rd.getEntity());
        if (rd.getQuantity() <= entitled) {
            this.addToReceivedList(rd, entityList);

        } else {
            System.out.println("Υπέρβαση ορίου για το είδος: " + rd.getEntity().getName());
        }
    }
    requestsList.reset();
}
public RequestDonationList getReceivedList() {
    return receivedList;
}

public Requests getRequestsList(){
    return requestsList;
}
 public String getName() {
    return name;
}

public String getPhone() {
    return phone;
}


}