import java.util.Comparator;

public class RequestDonationComparator implements Comparator<RequestDonation> {
    @Override
    public int compare(RequestDonation r1, RequestDonation r2) {
        return Integer.compare(r1.getEntity().getId(), r2.getEntity().getId());
    }
}
