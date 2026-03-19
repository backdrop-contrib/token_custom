<?php

/**
 * @file
 * Page callbacks and admin forms of the token_custom module.
 */

/**
 * Callback for the token_custom admin list page.
 *
 * @return string
 * The type page HTML.
 */
function token_custom_type_list_page() {
  $variables = array();
  $types = token_custom_type_load_multiple();

  foreach ($types as $type) {
    $row = array(
      check_plain($type->name),
      '[' . $type->machine_name . ']',
      check_plain($type->description),
    );

    // Do not show edit/delete links for the default custom type.
    if ($type->machine_name != TOKEN_CUSTOM_DEFAULT_TYPE) {
      $path_base = 'admin/structure/token-custom/type/' . $type->machine_name . '/';
      $links = array();
      $links['edit'] = array(
        'title' => t('Edit'),
        'href' => $path_base . 'edit',
      );
      $links['delete'] = array(
        'title' => t('Delete'),
        'href' => $path_base . 'delete',
      );
      $row[] = theme('links', array('links' => $links, 'attributes' => array('class' => array('links', 'inline'))));
    }
    else {
      $row[] = array('data' => t('Required'), 'class' => array('description'));
    }

    $variables['rows'][] = $row;
  }

  $variables['header'] = array(
    t('Name'),
    t('Machine name'),
    t('Description'),
    t('Operations'),
  );

  return theme('table', $variables);
}

/**
 * Callback for the token_custom token list page.
 *
 * @return string
 * The token list page HTML.
 */
function token_custom_list_page() {
  $tokens = token_custom_load_multiple();
  $token_admin = user_access('administer custom tokens');
  $token_info = token_info();
  $variables = array();

  foreach ($tokens as $token) {
    // Attempt to render a demo value if the token type doesn't require context data.
    if (empty($token_info['types'][$token->type]['needs-data'])) {
      $value = token_replace('[' . $token->type . ':' . $token->machine_name . ']');
    }
    else {
      $value = array('data' => t('Context required'), 'class' => array('description'));
    }

    $row = array(
      check_plain($token->name),
      '[' . $token->type . ':' . $token->machine_name . ']',
      check_plain($token->description),
      $value,
    );

    if ($token_admin) {
      $links = array();
      $links['edit'] = array(
        'title' => t('Edit'),
        'href' => 'admin/structure/token-custom/' . $token->machine_name . '/edit',
      );
      $links['delete'] = array(
        'title' => t('Delete'),
        'href' => 'admin/structure/token-custom/' . $token->machine_name . '/delete',
      );
      $row[] = theme('links', array('links' => $links, 'attributes' => array('class' => array('links', 'inline'))));
    }

    $variables['rows'][] = $row;
  }

  if (empty($variables['rows'])) {
    $variables['rows'][] = array(
      array(
        'data' => t('No custom tokens available. <a href="@url">Add one now</a>.', array('@url' => url('admin/structure/token-custom/add'))),
        'colspan' => $token_admin ? 5 : 4,
      ),
    );
  }

  $variables['header'] = array(
    t('Name'),
    t('Token Name'),
    t('Description'),
    t('Example'),
  );

  if ($token_admin) {
    $variables['header'][] = t('Operations');
  }

  return theme('table', $variables);
}

/**
 * The add/edit token form.
 *
 * @param array $form
 * The form array.
 * @param array $form_state
 * The form state.
 * @param string $op
 * Either 'add' or 'edit', according to the operation performed.
 * @param object $token
 * If $op is 'edit', $token contains the loaded token to edit.
 *
 * @return array
 * The token edit/add form.
 */
function token_custom_edit_form($form, &$form_state, $op, $token = NULL) {
  $form_state['token_custom']['op'] = $op;
  $form_state['token_custom']['token'] = $token;

  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Token name'),
    '#description' => t("The token's readable name."),
    '#default_value' => $token ? $token->name : '',
    '#maxlength' => 128,
    '#required' => TRUE,
  );

  $form['machine_name'] = array(
    '#type' => 'machine_name',
    '#title' => t('Token machine name'),
    '#default_value' => $token ? $token->machine_name : '',
    '#maxlength' => 32,
    '#disabled' => (bool) $token,
    '#machine_name' => array(
      'exists' => 'token_custom_load',
      'replace' => '-',
      'replace_pattern' => '[^a-z0-9\-]+',
    ),
  );

  $form['description'] = array(
    '#type' => 'textfield',
    '#title' => t('Token description'),
    '#description' => t("Appears in the token browser list."),
    '#default_value' => $token ? $token->description : '',
    '#maxlength' => 255,
    '#required' => TRUE,
  );

  $token_info = token_info();
  $options = array();
  foreach ($token_info['types'] as $type => $info) {
    $options[$type] = $info['name'];
    if (!empty($info['needs-data'])) {
      $options[$type] .= ' (' . t('Context: !data', array('!data' => $info['needs-data'])) . ')';
    }
  }

  $form['type'] = array(
    '#type' => 'select',
    '#title' => t('Token type'),
    '#description' => t('The type determines which context data (Node, User, etc.) is available to the token.'),
    '#options' => $options,
    '#default_value' => $token ? $token->type : TOKEN_CUSTOM_DEFAULT_TYPE,
    '#required' => TRUE,
  );

$form['content'] = array(
    '#type' => 'text_format',
    '#title' => t('Token Content'),
    '#description' => t('Enter the text this token should display. You may use other tokens here.') . '<br />' .
                      '<strong>' . t('Tip:') . '</strong> ' .
                      t('If this token is for a single line (like a company name), use a text format that has "Convert line breaks into HTML" disabled to avoid automatic &lt;p&gt; tags.'),
    '#default_value' => isset($token->content) ? $token->content : '',
    // Fallback to default format, avoiding the deprecated 'php_code'.
    '#format' => isset($token->format) ? $token->format : filter_default_format(),
    '#rows' => 5,
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['save'] = array(
    '#type' => 'submit',
    '#value' => t('Save token'),
  );

  if ($op == 'edit') {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
      '#limit_validation_errors' => array(),
    );
  }

  return $form;
}

/**
 * The add/edit token type form.
 *
 * @param array $form
 * The token type edit form.
 * @param array $form_state
 * The form state.
 * @param string $op
 * Either 'add' or 'edit', according to the operation performed.
 * @param object $type
 * If $op is 'edit', $type contains the loaded token type to edit.
 *
 * @return array
 * The complete form array.
 */
function token_custom_type_edit_form($form, &$form_state, $op, $type = NULL) {
  $form_state['token_custom']['op'] = $op;
  $form_state['token_custom']['type'] = $type;

  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t("Token type's name"),
    '#default_value' => $type ? $type->name : '',
    '#maxlength' => 255,
    '#required' => TRUE,
  );

  $form['machine_name'] = array(
    '#type' => 'machine_name',
    '#title' => t("Token type's machine name"),
    '#default_value' => $type ? $type->machine_name : '',
    '#maxlength' => 32,
    '#disabled' => (bool) $type,
    '#machine_name' => array(
      'exists' => 'token_custom_type_load',
      'replace' => '-',
      'replace_pattern' => '[^a-z0-9\-]+',
    ),
  );

  $form['description'] = array(
    '#type' => 'textfield',
    '#title' => t('Token type description'),
    '#default_value' => $type ? $type->description : '',
    '#required' => TRUE,
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['save'] = array(
    '#type' => 'submit',
    '#value' => t('Save token type'),
  );

  if ($op == 'edit') {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
      '#limit_validation_errors' => array(),
    );
  }

  return $form;
}

/**
 * Submit callback for token_custom_type_edit_form.
 *
 * @param array $form
 * The form array.
 * @param array $form_state
 * The submitted form state.
 */
function token_custom_type_edit_form_submit($form, &$form_state) {
  if (isset($form_state['triggering_element']['#value']) && $form_state['triggering_element']['#value'] == t('Delete')) {
    $form_state['redirect'] = 'admin/structure/token-custom/type/' . $form_state['values']['machine_name'] . '/delete';
    return;
  }

  $type = (object) array(
    'name' => $form_state['values']['name'],
    'machine_name' => $form_state['values']['machine_name'],
    'description' => $form_state['values']['description'],
  );

  token_custom_type_save($type);
  backdrop_set_message(t('Token type %name saved.', array('%name' => $type->name)));
  $form_state['redirect'] = 'admin/structure/token-custom/type';
}

/**
 * Submit handler for the custom token admin form.
 *
 * @param array $form
 * The form array.
 * @param array $form_state
 * The form state array.
 */
function token_custom_edit_form_submit($form, &$form_state) {
  if (isset($form_state['triggering_element']['#value']) && $form_state['triggering_element']['#value'] == t('Delete')) {
    $form_state['redirect'] = 'admin/structure/token-custom/' . $form_state['values']['machine_name'] . '/delete';
    return;
  }

  $token = (object) array(
    'name' => $form_state['values']['name'],
    'machine_name' => $form_state['values']['machine_name'],
    'description' => $form_state['values']['description'],
    'type' => $form_state['values']['type'],
    'content' => $form_state['values']['content']['value'],
    'format' => $form_state['values']['content']['format'],
    'is_new' => $form_state['token_custom']['op'] == 'add',
  );

  if (token_custom_save($token)) {
    backdrop_set_message(t('Token %name saved.', array('%name' => $token->name)));
  }
  else {
    backdrop_set_message(t('Failed to save token %name.', array('%name' => $token->name)), 'error');
  }

  $form_state['redirect'] = 'admin/structure/token-custom';
}

/**
 * Confirm custom token delete action.
 *
 * @param array $form
 * The delete token form.
 * @param array $form_state
 * Form state array.
 * @param object $token
 * The token object to delete.
 *
 * @return array
 * The complete form.
 */
function token_custom_delete_confirm_form($form, &$form_state, $token) {
  $form_state['token_custom']['token'] = $token;
  return confirm_form(
    $form,
    t('Are you sure you want to delete the token %name?', array('%name' => $token->name)),
    'admin/structure/token-custom',
    t('This action cannot be undone.'),
    t('Delete'),
    t('Cancel')
  );
}

/**
 * Delete token form submit callback.
 *
 * @param array $form
 * The form array.
 * @param array $form_state
 * The form state array.
 */
function token_custom_delete_confirm_form_submit($form, &$form_state) {
  token_custom_delete($form_state['token_custom']['token']->machine_name);
  backdrop_set_message(t('Token %name deleted.', array('%name' => $form_state['token_custom']['token']->name)));
  $form_state['redirect'] = 'admin/structure/token-custom';
}

/**
 * Confirm custom token type delete action.
 *
 * @param array $form
 * The delete token form.
 * @param array $form_state
 * Form state array.
 * @param object $token_type
 * The token type to delete.
 *
 * @return array
 * The complete form.
 */
function token_custom_type_delete_confirm_form($form, &$form_state, $token_type) {
  $form_state['token_custom']['token_type'] = $token_type;
  return confirm_form(
    $form,
    t('Are you sure you want to delete the token type %name?', array('%name' => $token_type->name)),
    'admin/structure/token-custom/type',
    t('Any tokens using this type will be moved to the "Custom" type. This action cannot be undone.'),
    t('Delete'),
    t('Cancel')
  );
}

/**
 * Delete token type form submit callback.
 *
 * @param array $form
 * The form array.
 * @param array $form_state
 * The form state array.
 */
function token_custom_type_delete_confirm_form_submit($form, &$form_state) {
  token_custom_type_delete($form_state['token_custom']['token_type']->machine_name);
  backdrop_set_message(t('Token type %name deleted.', array('%name' => $form_state['token_custom']['token_type']->name)));
  $form_state['redirect'] = 'admin/structure/token-custom/type';
}
