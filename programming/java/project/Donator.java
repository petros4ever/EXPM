public class Donator extends User{
      private Offers offersList;
      
      public Donator(String name,String phone)
      {
          super(name,phone);
          this.offersList=new Offers();
       }
       
      public void addOffer(Offer offer) 
    {
        offersList.add(offer);
    }

    public void removeOffer(Offer offer)
   {
        offersList.remove(offer);
    }

    public void commitOffers() 
    {
        offersList.commit();
    }

    public Offers getOffersList() 
     {
        return offersList;
    }

}