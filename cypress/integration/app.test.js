describe('/login', () => {
  it('does the right thing on successful login', () => {
    cy.server();

    cy.route({
      method: 'POST',
      url: '/auth/login',
      status: 201,
      response: {}
    });

    cy.visit('/login');

    cy.get("input[name='username']").type('test');
    cy.get("input[name='password']").type('WRONG');
    cy.contains('login').click();
    cy.location().should((loc) => {
      expect(loc.pathname).to.eq('/workspace');
    });
  });
  
  it('shows error message if the username and password is wrong', () => {
    cy.server();

    cy.route({
      method: 'POST',
      url: '/auth/login',
      status: 401,
      response: {}
    });

    cy.visit('/login');

    cy.get("input[name='username']").type('test');
    cy.get("input[name='password']").type('WRONG');
    cy.contains('login').click();
    cy.contains('nope');
  });
});