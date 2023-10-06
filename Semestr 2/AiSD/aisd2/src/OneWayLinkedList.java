import java.util.Iterator;
import java.util.ListIterator;
import java.util.NoSuchElementException;

public class OneWayLinkedList<E> implements IList<E> {

    private class Element {
        E object;
        Element next = null;

        public Element(E e) {
            this.object = e;
        }
    }

    Element sentinel;

    private class InnerIterator implements Iterator<E> {
        private Element currentElement;

        public InnerIterator() {
            currentElement = sentinel;
        }

        @Override
        public boolean hasNext() {
            return currentElement.next != null;
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
        Element newElem = new Element(e);
        if (sentinel.next == null) {
            sentinel.next = newElem;
            return true;
        }
        Element tail = sentinel.next;
        while (tail.next != null) {
            tail = tail.next;
        }
        tail.next = newElem;
        return true;
    }
    
    private Element getElement(int index) throws NoSuchElementException {
        if (index < 0) {
            throw new NoSuchElementException();
        }

        Element actElem = sentinel.next;
        while (index > 0 && actElem != null) {
            index--;
            actElem = actElem.next;
        }
        if (actElem == null) {
            throw new NoSuchElementException();
        }
        
        return actElem;
    }
    
    public void removeEven() {
        int index = 0;
        
        Element before = sentinel;
        Element current = sentinel.next;
        
        while(current != null) {
            if(index % 2 == 0) {
                before.next = current.next;
            }
            else {
                before = current;
            }
            current = current.next;
            index++;
        }
    }

    @Override
    public void add(int index, E e) throws NoSuchElementException {
        if(index < 0) {
            throw new NoSuchElementException();
        }
        
        Element backElement = index == 0 ? sentinel : getElement(index - 1);
        
        Element createdElement = new Element(e);
        createdElement.next = backElement.next;
        backElement.next = createdElement;
    }

    @Override
    public void clear() {
        sentinel.next = null;
    }

    @Override
    public boolean contains(E e) {
        return indexOf(e) >= 0;
    }

    @Override
    public E get(int index) throws NoSuchElementException {
        return getElement(index).object;
    }

    @Override
    public E set(int index, E e) throws NoSuchElementException {
        Element element = getElement(index);
        E previousValue = element.object;
        getElement(index).object = e;
        
        return previousValue;
    }

    @Override
    public int indexOf(E e) {
        int pos = 0;
        Element actualElement = sentinel.next;

        while (actualElement != null) {
            if (actualElement.object.equals(e)) {
                return pos;
            }
            pos++;
            actualElement = actualElement.next;
        }
        return -1;
    }

    @Override
    public boolean isEmpty() {
        return sentinel.next != null;
    }

    @Override
    public E remove(int index) throws NoSuchElementException {
        if(index < 0) {
            throw new NoSuchElementException();
        }
        
        Element backElement = index == 0 ? sentinel : getElement(index - 1);
        if(backElement.next == null) {
            throw new NoSuchElementException();
        }
        
        Element removed = backElement.next;
        backElement.next = backElement.next.next;
        return removed.object;
    }

    @Override
    public boolean remove(E e) {
        Element current = sentinel;
        
        while(current.next != null) {
            if(current.next.object.equals(e)) {
                current.next = current.next.next;
                return true;
            }
            current = current.next;
        }
        return false;
    }

    @Override
    public int size() {
        int size = 0;
        Element tail = sentinel.next;

        while (tail != null) {
            size++;
            tail = tail.next;
        }
        return size;
    }
}
