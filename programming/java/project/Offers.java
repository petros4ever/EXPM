import java.util.ArrayList;
public class Offers extends RequestDonationList {

    public Offers() {
        super();
    }

    public void commit(RequestDonationList currentDonations, ArrayList<Entity> entityList) {
        for (RequestDonation offer : new ArrayList<>(getList())) {
            try {
                
                boolean found = entityList.stream()
                    .anyMatch(e -> e.getId() == offer.getEntity().getId());

                if (!found) {
                    throw new Exception("Το entity " + offer.getEntity().getName() + " δεν υπάρχει στον οργανισμό.");
                }

                
                currentDonations.add(offer, entityList);

            } catch (Exception ex) {
                System.out.println("❗ Δεν έγινε commit για " + offer.getEntity().getName() + ": " + ex.getMessage());
            }
        }

        
        reset();
    }
}
