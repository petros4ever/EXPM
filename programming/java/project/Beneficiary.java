public class Benificiary extends User{
     private int nopersons=1;
     private RequestDonationList receivedList;
     private Requests requestsList;
     
     public Beneficiary(String name, String phone, int noPersons) 
    {
        super(name, phone);
        this.noPersons = noPersons;
        this.receivedList = new RequestDonationList();
        this.requestsList = new Requests();
    }
    
     public void addRequest(Request r) {
        requestsList.add(r);
    }

    public void removeRequest(Request r) {
        requestsList.remove(r);
    }

    public void commitRequests() {
        requestsList.commit();
    }

    public void addToReceivedList(RequestDonation rd) {
        receivedList.add(rd);
    }
}