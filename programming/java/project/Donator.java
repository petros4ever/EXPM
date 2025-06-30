import java.util.ArrayList;
public class Donator extends User{
      private Offers offersList;
      
      public Donator(String name,String phone)
      {
          super(name,phone);
          this.offersList=new Offers();
       }
       
    public void addOffer(RequestDonation rd, ArrayList<Entity> entityList) throws Exception {
        offersList.add(rd, entityList);
    }

    public void removeOffer(Entity entity) {
        offersList.remove(entity);
    }

    public void modifyOffer(int entityId, double newQuantity) {
        offersList.modify(entityId, newQuantity);
    }

    public void commitOffers(RequestDonationList currentDonations, ArrayList<Entity> entityList) {
        offersList.commit(currentDonations, entityList);
    }

    public Offers getOffersList() {
        return offersList;
    }

   public String getName() {
    return name;
}

public String getPhone() {
    return phone;
}

}