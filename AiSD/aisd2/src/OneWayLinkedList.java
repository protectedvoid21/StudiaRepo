import java.util.Iterator;
import java.util.ListIterator;
import java.util.NoSuchElementException;

public class OneWayLinkedList<E> implements IList<E>{

    private class Element{
        E object;
        Element next = null;
        
        public Element(E e) {
            this.object=e;
        }
    }

    Element sentinel;

    private class InnerIterator implements Iterator<E>{
        private Element currentElement;
        
        public InnerIterator() {
            currentElement = sentinel;
        }
        @Override
        public boolean hasNext() {
            return currentElement != null;
        }

        @Override
        public E next() {
            currentElement = currentElement.next;
            return currentElement.object;
        }
    }

    public OneWayLinkedList() {
        sentinel = new Element(null);
    }

    @Override
    public Iterator<E> iterator() {
        return new InnerIterator();
    }

    @Override
    public ListIterator<E> listIterator() {
        throw new UnsupportedOperationException();
    }

    @Override
    public boolean add(E e) {
        Element element = new Element(e);
        
        Element last = sentinel;
        while(last.next != null) {
            last = last.next;
        }
        last.next = element;
        return true;
    }

    @Override
    public void add(int index, E element) throws NoSuchElementException {
        // TODO Auto-generated method stub

    }

    @Override
    public void clear() {
        // TODO Auto-generated method stub

    }

    @Override
    public boolean contains(E element) {
        return indexOf(element) >= 0;
    }

    @Override
    public E get(int index) throws NoSuchElementException {
        // TODO Auto-generated method stub
        return null;
    }

    @Override
    public E set(int index, E element) throws NoSuchElementException {
        // TODO Auto-generated method stub
        return null;
    }

    @Override
    public int indexOf(E element) {
        int pos = 0;
        Element actualElement = sentinel;
        
        while(actualElement != null) {
            if(actualElement.object.equals(element)) {
                return pos;
            }
            pos++;
            actualElement = actualElement.next;
        }
        return -1;
    }

    @Override
    public boolean isEmpty() {
        // TODO Auto-generated method stub
        return false;
    }

    @Override
    public E remove(int index) throws NoSuchElementException {
        // TODO Auto-generated method stub
        return null;
    }

    @Override
    public boolean remove(E e) {
        // TODO Auto-generated method stub
        return false;
    }

    @Override
    public int size() {
        // TODO Auto-generated method stub
        return 0;
    }

}
