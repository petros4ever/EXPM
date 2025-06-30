import java.util.ArrayList;

public class RequestDonationList {
    private ArrayList<RequestDonation> rdEntities;

    public RequestDonationList() {
        rdEntities = new ArrayList<>();
    }

    public void add(RequestDonation rd, ArrayList<Entity> entityList) throws Exception {
    boolean entityExists = false;
    for (Entity e : entityList) {
        if (e.getId() == rd.getEntity().getId()) {
            entityExists = true;
            break;
        }
    }

    if (!entityExists) {
        throw new Exception("Το entity δεν υπάρχει στην entityList του οργανισμού.");
    }

    for (RequestDonation existing : rdEntities) {
        if (existing.getEntity().getId() == rd.getEntity().getId()) {
            double newQuantity = existing.getQuantity() + rd.getQuantity();
            rdEntities.set(rdEntities.indexOf(existing),
                new RequestDonation(rd.getEntity(), newQuantity));
            return;
        }
    }

    rdEntities.add(rd);
}

    public void remove(Entity e) {
        rdEntities.removeIf(rd -> rd.getEntity().getId() == e.getId());
    }

   public RequestDonation get(int entityId) {
    for (RequestDonation rd : rdEntities) {
        if (rd.getEntity().getId() == entityId) return rd;
    }
    return null;
}


    public ArrayList<RequestDonation> getList() {
        return rdEntities;
    }
 
    public void modify(int entityId, double newQuantity) {
    for (RequestDonation rd : rdEntities) {
        if (rd.getEntity().getId() == entityId) {
            rdEntities.set(rdEntities.indexOf(rd),
                new RequestDonation(rd.getEntity(), newQuantity));
            return;
        }
    }
    System.out.println("Το entity δεν βρέθηκε για τροποποίηση.");
}
public void monitor() {
    if (rdEntities.isEmpty()) {
        System.out.println("📭 Η λίστα είναι κενή.");
        return;
    }
    for (RequestDonation rd : rdEntities) {
        System.out.println("📦 " + rd.getEntity().getName() +
                           " - Ποσότητα: " + rd.getQuantity());
    }
}
public void reset() {
    rdEntities.clear();
}

}
