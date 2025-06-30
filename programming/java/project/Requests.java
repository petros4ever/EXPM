import java.util.ArrayList;
public class Requests extends RequestDonationList {
    private Beneficiary beneficiary;          
    private RequestDonationList currentDonations; 

    public Requests(Beneficiary beneficiary, RequestDonationList currentDonations) {
        super();
        this.beneficiary = beneficiary;
        this.currentDonations = currentDonations;
    }
public boolean validRequestDonation(RequestDonation rd) {
    Entity e = rd.getEntity();
    double requestedQty = rd.getQuantity();

    if (e instanceof Material) {
        double entitledQty = beneficiary.getEntitledQuantity(e); 
        double alreadyReceived = 0.0;

        RequestDonation received = beneficiary.getReceivedList().get(e.getId());
        if (received != null) {
            alreadyReceived = received.getQuantity();
        }

        return requestedQty + alreadyReceived <= entitledQty;
    }
        return true;
}

public void add(RequestDonation rd, ArrayList<Entity> entityList) throws Exception {
    
    boolean existsInOrg = entityList.stream()
        .anyMatch(e -> e.getId() == rd.getEntity().getId());

    if (!existsInOrg) {
        throw new Exception("❌ Το entity δεν ανήκει στον οργανισμό.");
    }

    
    if (!validRequestDonation(rd)) {
        throw new Exception("⛔ Η ζητούμενη ποσότητα ξεπερνά το επιτρεπτό όριο.");
    }

    
    super.add(rd, entityList);
}

public void modify(int entityId, double newQty, ArrayList<Entity> entityList) throws Exception {
    RequestDonation rd = get(entityId);
    if (rd == null) throw new Exception("Το entity δεν υπάρχει στη λίστα αιτημάτων.");

    RequestDonation updated = new RequestDonation(rd.getEntity(), newQty);
    if (!entityList.contains(rd.getEntity())) {
        throw new Exception("Το entity δεν υπάρχει στον οργανισμό.");
    }

    if (!validRequestDonation(updated)) {
        throw new Exception("⛔ Δεν δικαιούσαι τέτοια ποσότητα.");
    }

    super.modify(entityId, newQty);
}
public void commit(ArrayList<Entity> entityList) {
    ArrayList<RequestDonation> list = getList();

    for (RequestDonation rd : new ArrayList<>(list)) {
        try {
           
            boolean exists = entityList.stream().anyMatch(e -> e.getId() == rd.getEntity().getId());
            if (!exists) throw new Exception("Entity δεν υπάρχει στον οργανισμό.");

            
            if (!validRequestDonation(rd)) {
                throw new Exception("Υπέρβαση δικαιώματος για " + rd.getEntity().getName());
            }

            
            RequestDonation available = currentDonations.get(rd.getEntity().getId());
            if (available == null || available.getQuantity() < rd.getQuantity()) {
                throw new Exception("Δεν υπάρχει αρκετή ποσότητα διαθέσιμη στο σύστημα.");
            }

            
            double newQty = available.getQuantity() - rd.getQuantity();
            currentDonations.modify(rd.getEntity().getId(), newQty);
            beneficiary.getReceivedList().add(rd,entityList);
            remove(rd.getEntity());
        } catch (Exception ex) {
            System.out.println("❗ Δεν ολοκληρώθηκε η παροχή: " + ex.getMessage());
        }
    }
}
}