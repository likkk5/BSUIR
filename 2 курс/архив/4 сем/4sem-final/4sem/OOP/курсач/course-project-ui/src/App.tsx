import { Container } from 'react-bootstrap';
import { AuthProvider } from './contexts/AuthContext';
import Navigation from './components/Navigation';
import { AppRoutes } from './components/AppRoutes';


function App() {
  return (
    <>
      <AuthProvider>
        <Navigation/>
        <Container
          className="d-flex align-items-center justify-content-center"
          style={{ minHeight: '100vh' }}
        >
          <AppRoutes/>
        </Container>
      </AuthProvider>
    </>
  );
}

export default App;
