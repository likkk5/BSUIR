import React, { FunctionComponent, useRef } from 'react';
import { BookDTO } from '../types';
import { Button, Form } from 'react-bootstrap';

interface OwnProps {
  book?: BookDTO;
  bookAction: (book: Omit<BookDTO, 'id'>) => Promise<void>;
}

type Props = OwnProps;

const BookForm: FunctionComponent<Props> = ({ book, bookAction }) => {
  const titleRef = useRef<HTMLInputElement>(null!);
  const genreRef = useRef<HTMLInputElement>(null!);
  const authorRef = useRef<HTMLInputElement>(null!);
  const descriptionRef = useRef<HTMLInputElement>(null!);
  const depositPriceRef = useRef<HTMLInputElement>(null!);
  const amountRef = useRef<HTMLInputElement>(null!);
  const rentPriceRef = useRef<HTMLInputElement>(null!);

  const handleSubmit: React.FormEventHandler<HTMLFormElement> = async (e) => {
    e.preventDefault();
    await bookAction({
      title: titleRef.current.value,
      genre: genreRef.current.value,
      author: authorRef.current.value,
      description: descriptionRef.current.value,
      depositPrice: Number(depositPriceRef.current.value),
      amount: Number(amountRef.current.value),
      rentPrice: Number(rentPriceRef.current.value),
    });
  };

  return (
    <Form onSubmit={handleSubmit}>
      <Form.Group className="mb-3">
        <Form.Label>Title</Form.Label>
        <Form.Control type="text" defaultValue={book?.title} ref={titleRef} required readOnly={false}/>
      </Form.Group>
      <Form.Group className="mb-3">
        <Form.Label>Genre</Form.Label>
        <Form.Control type="text" defaultValue={book?.genre} ref={genreRef} required/>
      </Form.Group>
      <Form.Group className="mb-3">
        <Form.Label>Author</Form.Label>
        <Form.Control type="text" defaultValue={book?.author} ref={authorRef} required/>
      </Form.Group>
      <Form.Group className="mb-3">
        <Form.Label>Description</Form.Label>
        <Form.Control type="text" defaultValue={book?.description} ref={descriptionRef} required/>
      </Form.Group>
      <Form.Group className="mb-3">
        <Form.Label>Deposit price</Form.Label>
        <Form.Control type="number" defaultValue={book?.depositPrice} ref={depositPriceRef} required/>
      </Form.Group>
      <Form.Group className="mb-3">
        <Form.Label>Amount</Form.Label>
        <Form.Control type="number" defaultValue={book?.amount} ref={amountRef} required/>
      </Form.Group>
      <Form.Group className="mb-3">
        <Form.Label>RentPrice</Form.Label>
        <Form.Control type="number" defaultValue={book?.rentPrice} ref={rentPriceRef} required/>
      </Form.Group>
      <Button className="w-100 mb-3" type="submit">
        Submit
      </Button>
    </Form>
  );
};

export default BookForm;
