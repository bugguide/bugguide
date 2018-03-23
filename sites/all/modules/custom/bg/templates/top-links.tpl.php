<?php if ($logged_in): ?>
  <ul class="is-flex">
    <li>
      <a class="button is-primary mr-2" href="/node/6/bgimage">
        <span class="icon">
          <span class="fa fa-bug" aria-hidden="true"></span>
        </span>
        <span>ID request</span>
      </a>
    </li>
    <li>
      <a class="button is-tan mr-2" href="/user">
        <span class="icon">
          <span class="fa fa-user-circle" aria-hidden="true"></span>
        </span>
        <span>My Account</span>
      </a>
    </li>
    <li>
      <a class="button is-tan mr-2" href="https://www.biology-it.iastate.edu/bugguide-bug-report">
        <span class="icon">
          <span class="fa fa-bug" aria-hidden="true"></span>
        </span>
        <span>Report Bug</span>
      </a>
    </li>
    <li>
      <a class="button is-tan" title="Logout"href="/user/logout">
        <span>
          <span class="fa fa-sign-out" aria-hidden="true"></span>
        </span>
        <span class="sr-only">Logout</span>
      </a>
    </li>
  </ul>
<?php else: ?>
  <ul class="is-flex">
    <li>
      <a class="button is-tan mr-2" href="/user">
        <span class="icon">
          <span class="fa fa-sign-in" aria-hidden="true"></span>
        </span>
        <span>Login or Register</span>
      </a>
    </li>
  </ul>
<?php endif; ?>
